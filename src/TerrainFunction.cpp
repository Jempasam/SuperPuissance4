#include "TerrainFunction.h"

Object &Object::operator=(Object object)
{
    category=object.category;
    type=object.type;
    state=object.state;
    timer=object.timer;
    cGroup=object.cGroup;
    objectTex=object.objectTex;
    stateTex=object.stateTex;
    player=object.player;
    identifier=object.identifier;

    colorOffset=object.colorOffset;

    return *this;
}
ArenaObject::ArenaObject()
{
    Argument newArg;Value newValue;
    newValue.type=ArgumentType::value;
    newValue.operat=ArgOperator::plus;
    newArg.values.push_back(newValue);

    newArg.values[0].value.push_back(100);
    chanceToSpawn=newArg;

    newArg.values[0].value.push_back(0);
    posRandOffset=newArg;

    newArg.values[0].value.push_back(100);
    chanceToSpawn=newArg;
}
Object::Object()
{
    identifier=getRandomNumber(RAND_MAX)+getRandomNumber(RAND_MAX)*RAND_MAX;
}
void Terrain::create(int X,int Y)
{
    terrain.clear();
    for(int x=0;x<X;x++)
    {
        std::vector<Cellule> ligne;
        for(int y=0;y<Y;y++)
        {
            ligne.push_back(Cellule());
        }
        terrain.push_back(ligne);
    }
}
void Terrain::drawTerrain(sf::RenderTexture &TARGET)
{
    float SIZEX=1000.0/terrain.size();float SIZEY=1000.0/terrain[0].size();
    TARGET.create(1000,1000);
    TARGET.clear(sf::Color::Red);
    for(int y=0;y<terrain[0].size();y++)
    {
        for(int x=0;x<terrain.size();x++)
        {
            drawTex(TARGET,*content::terrainSkin[skin].textures[0],
                    x*SIZEX,y*SIZEY,SIZEX,SIZEY);
        }
    }
    TARGET.display();
}
void Terrain::drawObjectAt(sf::RenderTexture &TARGET,int X,int Y)
{
    float SIZEX=1000.0/terrain.size();float SIZEY=1000.0/terrain[0].size();
    drawTex(TARGET,*content::terrainSkin[skin].textures[0],
                    X*SIZEX,Y*SIZEY,SIZEX,SIZEY);

    Cellule &cellule=terrain[X][Y];
    if(cellule.objects.size()==0);
    else
    {
        for(int i=0;i<cellule.objects.size();i++)
        {
            ObjectType &objectType=content::objectType[cellule.objects[i].type];
            ObjectState &objectState=content::objectState[cellule.objects[i].state];
            Object &object=cellule.objects[i];

            if(objectType.textures.size()!=0)
            {
                int &objectNTex=object.objectTex;

                sf::Texture &objectTex=*getTexFromList(objectType.textures,objectNTex);
                sf::Color &color=objectState.color;

                if(&objectTex!=&global::nullTex)
                    drawTex(TARGET,objectTex,X*SIZEX,Y*SIZEY,SIZEX,SIZEY,int(color.r),int(color.g),int(color.b),int(color.a));
            }
            if(objectState.textures.size()!=0)
            {
                int &stateNTex=object.stateTex;

                sf::Texture &stateTex=*getTexFromList(objectState.textures,stateNTex);

                if(&stateTex!=&global::nullTex)
                    drawTex(TARGET,stateTex,X*SIZEX,Y*SIZEY,SIZEX,SIZEY);
            }
        }
    }
}
void Terrain::drawObjects(sf::RenderTexture &TARGET)
{
    TARGET.create(1000,1000);
    TARGET.clear(sf::Color::Transparent);
    for(int y=0;y<terrain[0].size();y++)
    {
        for(int x=0;x<terrain.size();x++)
        {
            drawObjectAt(TARGET,x,y);
        }
    }
    TARGET.display();
}
void Terrain::moveObject(sf::RenderTexture &TARGET,int X,int Y,int objectNum,int newX,int newY)
{
    if(newX<terrain.size()&&newX>=0
       &&newY<terrain[0].size()&&newY>=0)
    {
        terrain[newX][newY].objects.push_back(terrain[X][Y].objects[objectNum]);
        terrain[X][Y].objects.erase(terrain[X][Y].objects.begin()+objectNum);
        drawObjectAt(TARGET,X,Y);
        drawObjectAt(TARGET,newX,newY);
    }
    else
    {
        terrain[X][Y].objects.erase(terrain[X][Y].objects.begin()+objectNum);
        drawObjectAt(TARGET,X,Y);
    }
}
void Terrain::drawCursor(sf::RenderTexture &TARGET)
{
    float SIZEX=1000.0/terrain.size();float SIZEY=1000.0/terrain[0].size();
    TARGET.create(1000,1000);
    TARGET.clear(sf::Color::Transparent);

    for(int y=0;y<terrain[0].size();y++)
    {
        for(int x=0;x<terrain.size();x++)
        {
            for(int i=0;i<content::teams.size();i++)
            {
                ComplexZone &cursorZone=content::spawnerHand[content::teams[i].spawnerHand].spawner[content::teams[i].selectedCategory][content::teams[i].selectedSpawner].zone;

                if(cursorZone.isInZone(x,y))drawTex(TARGET,*content::teams[i].cursor2Tex,x*SIZEX,y*SIZEY,SIZEX,SIZEY);
            }
        }
    }

    for(int i=0;i<content::teams.size();i++)
    {
        drawTex(TARGET,*content::teams[i].cursorTex,
                content::teams[i].cursorPos.x*SIZEX,content::teams[i].cursorPos.y*SIZEY,
                SIZEX,SIZEY);
    }

    TARGET.display();

}
void Terrain::drawCursorAt(sf::RenderTexture &TARGET,int X,int Y)
{
    float SIZEX=1000.0/terrain.size();float SIZEY=1000.0/terrain[0].size();
    eraseQuad(TARGET,X*SIZEX,Y*SIZEY,SIZEX,SIZEY);


    for(int i=0;i<content::teams.size();i++)
    {
        ComplexZone &cursorZone=content::spawnerHand[content::teams[i].spawnerHand].spawner[content::teams[i].selectedCategory][content::teams[i].selectedSpawner].zone;
        if(cursorZone.isInZone(X,Y))drawTex(TARGET,*content::teams[i].cursor2Tex,X*SIZEX,Y*SIZEY,SIZEX,SIZEY);
    }

    for(int i=0;i<content::teams.size();i++)
    {
        if(content::teams[i].cursorPos.x==X&&content::teams[i].cursorPos.y==Y)
        {
            drawTex(TARGET,*content::teams[i].cursorTex,
                X*SIZEX,Y*SIZEY,
                SIZEX,SIZEY);
        }
    }

    TARGET.display();

}
void Terrain::spawnObject(sf::RenderTexture &TARGET,int teamNumber,int X,int Y)
{
    Team &team=content::teams[teamNumber];
    if(team.timer>0){return;}
    if(terrain[X][Y].objects.size()!=0)return;
    Spawner &spawner=content::spawnerHand[team.spawnerHand].spawner[team.selectedCategory][team.selectedSpawner];
    if(spawner.zone.isInZone(X,Y))
    {
        Object newObject; newObject.type=spawner.object; newObject.state=spawner.state;newObject.player=teamNumber;
        terrain[X][Y].objects.push_back(newObject);
        team.timer=spawner.timer;
        drawObjectAt(TARGET,X,Y);
    }
}
void Terrain::keyPressed(sf::RenderTexture &ObjMapTx,sf::RenderTexture &cursorTex,sf::Keyboard::Key key)
{
    for(int i=0;i<content::teams.size();i++)
    {

        int &cursorX=content::teams[i].cursorPos.x;
        int &cursorY=content::teams[i].cursorPos.y;


        if(content::keyConfig[i].up==key&&cursorY>0)
            {cursorY--; drawCursorAt(cursorTex,cursorX,cursorY); drawCursorAt(cursorTex,cursorX,cursorY+1);}
        else if(content::keyConfig[i].down==key&&cursorY<terrain.size()-1)
            {cursorY++; drawCursorAt(cursorTex,cursorX,cursorY); drawCursorAt(cursorTex,cursorX,cursorY-1);}
        else if(content::keyConfig[i].left==key&&cursorX>0)
            {cursorX--; drawCursorAt(cursorTex,cursorX,cursorY); drawCursorAt(cursorTex,cursorX+1,cursorY);}
        else if(content::keyConfig[i].right==key&&cursorX<terrain[0].size()-1)
            {cursorX++; drawCursorAt(cursorTex,cursorX,cursorY); drawCursorAt(cursorTex,cursorX-1,cursorY);}

        else if(content::keyConfig[i].createObject==key)spawnObject(ObjMapTx,i,content::teams[i].cursorPos.x,content::teams[i].cursorPos.y);

        else if(content::keyConfig[i].spawnNext==key)
        {
            content::teams[i].selectedSpawner++;
            if(content::teams[i].selectedSpawner>=content::spawnerHand[content::teams[i].spawnerHand].spawner[content::teams[i].selectedCategory].size())
                content::teams[i].selectedSpawner=0;
        }
        else if(content::keyConfig[i].spawnPrevious==key)
        {
            content::teams[i].selectedSpawner--;
            if(content::teams[i].selectedSpawner<0)
                content::teams[i].selectedSpawner=content::spawnerHand[content::teams[i].spawnerHand].spawner[content::teams[i].selectedCategory].size()-1;
        }

        else if(content::keyConfig[i].categoryNext==key)
        {
            content::teams[i].selectedCategory++;
            if(content::teams[i].selectedCategory>=content::spawnerHand[content::teams[i].spawnerHand].spawner.size())
                content::teams[i].selectedCategory=0;
            if(content::teams[i].selectedSpawner>=content::spawnerHand[content::teams[i].spawnerHand].spawner[content::teams[i].selectedCategory].size())
                content::teams[i].selectedSpawner=0;
        }
        else if(content::keyConfig[i].categoryPrevious==key)
        {
            content::teams[i].selectedCategory--;
            if(content::teams[i].selectedCategory<0)
                content::teams[i].selectedCategory=content::spawnerHand[content::teams[i].spawnerHand].spawner.size()-1;

            if(content::teams[i].selectedSpawner>=content::spawnerHand[content::teams[i].spawnerHand].spawner[content::teams[i].selectedCategory].size())
                content::teams[i].selectedSpawner=content::spawnerHand[content::teams[i].spawnerHand].spawner[content::teams[i].selectedCategory].size()-1;
        }
    }
}
/*void Terrain::testKeyPressed(sf::RenderTexture &ObjMapTx,sf::RenderTexture &cursorTex)
{
    for(int i=0;i<content::teams.size();i++)
    {

        int &cursorX=content::teams[i].cursorPos.x;
        int &cursorY=content::teams[i].cursorPos.y;


        if(content::keyConfig[i].up==key&&cursorY>0)
            {cursorY--; drawCursorAt(cursorTex,cursorX,cursorY); drawCursorAt(cursorTex,cursorX,cursorY+1);}
        else if(content::keyConfig[i].down==key&&cursorY<terrain.size()-1)
            {cursorY++; drawCursorAt(cursorTex,cursorX,cursorY); drawCursorAt(cursorTex,cursorX,cursorY-1);}
        else if(content::keyConfig[i].left==key&&cursorX>0)
            {cursorX--; drawCursorAt(cursorTex,cursorX,cursorY); drawCursorAt(cursorTex,cursorX+1,cursorY);}
        else if(content::keyConfig[i].right==key&&cursorX<terrain[0].size()-1)
            {cursorX++; drawCursorAt(cursorTex,cursorX,cursorY); drawCursorAt(cursorTex,cursorX-1,cursorY);}

        else if(content::keyConfig[i].createObject==key)spawnObject(ObjMapTx,i,content::teams[i].cursorPos.x,content::teams[i].cursorPos.y);

        else if(content::keyConfig[i].spawnNext==key)
        {
            content::teams[i].selectedSpawner++;
            if(content::teams[i].selectedSpawner>=content::spawnerHand[content::teams[i].spawnerHand].spawner[content::teams[i].selectedCategory].size())
                content::teams[i].selectedSpawner=0;
        }
        else if(content::keyConfig[i].spawnPrevious==key)
        {
            content::teams[i].selectedSpawner--;
            if(content::teams[i].selectedSpawner<0)
                content::teams[i].selectedSpawner=content::spawnerHand[content::teams[i].spawnerHand].spawner[content::teams[i].selectedCategory].size()-1;
        }

        else if(content::keyConfig[i].categoryNext==key)
        {
            content::teams[i].selectedCategory++;
            if(content::teams[i].selectedCategory>=content::spawnerHand[content::teams[i].spawnerHand].spawner.size())
                content::teams[i].selectedCategory=0;
            if(content::teams[i].selectedSpawner>=content::spawnerHand[content::teams[i].spawnerHand].spawner[content::teams[i].selectedCategory].size())
                content::teams[i].selectedSpawner=0;
        }
        else if(content::keyConfig[i].categoryPrevious==key)
        {
            content::teams[i].selectedCategory--;
            if(content::teams[i].selectedCategory<0)
                content::teams[i].selectedCategory=content::spawnerHand[content::teams[i].spawnerHand].spawner.size()-1;

            if(content::teams[i].selectedSpawner>=content::spawnerHand[content::teams[i].spawnerHand].spawner[content::teams[i].selectedCategory].size())
                content::teams[i].selectedSpawner=content::spawnerHand[content::teams[i].spawnerHand].spawner[content::teams[i].selectedCategory].size()-1;
        }
    }
}*/
int Terrain::getValueFromVariable(int VariableNum,int X,int Y,int objectNum)
{
    if(VariableNum==0)return terrain[X][Y].objects[objectNum].type;
    else if(VariableNum==1)return terrain[X][Y].objects[objectNum].state;
    else if(VariableNum==3)return terrain[X][Y].objects.size();
}
void useArenaObject(Terrain &terrain,ArenaObject &aobject)
{
    ScriptTarget target;
    int X1=treatArg(aobject.X1,target,terrain);int Y1=treatArg(aobject.Y1,target,terrain);
    int X2=treatArg(aobject.X2,target,terrain);int Y2=treatArg(aobject.Y2,target,terrain);
    for(int x=X1;x<=X2;x++)
    {
        for(int y=Y1;y<=Y2;y++)
        {

            if(x>=0&&y>=0 && x<terrain.terrain.size()&&y<terrain.terrain[0].size())
            {
                target.X=x;target.Y=y;
                if(aobject.doClear)terrain.terrain[x][y].objects.clear();

                int type=getRandomNumber(aobject.objectTypes.size()-1);
                int state;
                if(aobject.typeStateSync)state=type;
                else state=getRandomNumber(aobject.ObjectStates.size()-1);

                Object newObject;
                newObject.state=treatArg(aobject.ObjectStates[state],target,terrain);
                newObject.type=treatArg(aobject.objectTypes[type],target,terrain);
                newObject.player=aobject.team;
                terrain.terrain[x][y].objects.push_back(newObject);
            }

        }
    }
}
void useArena(Terrain &terrain,Arena &arena)
{
    for(int i=0;i<arena.objects.size();i++)
    {
        useArenaObject(terrain,arena.objects[i]);
    }
}
/*bool Terrain::ifAssociateWith2(Association &association,int X,int Y,int NUM)
{
    Object centerObject=terrain[X][Y].objects[NUM];
    int cellx,celly;

    for(int centerI=0;centerI<association.blocks.size();centerI++)
    if(centerObject.state==association.blocks[centerI].state&&
       centerObject.type==association.blocks[centerI].type)
    {
        AssociateBlock centerBlock=association.blocks[centerI];
        bool associated=true;

        for(int targI=0;targI<association.blocks.size();targI++)
        {
            AssociateBlock targBlock=association.blocks[targI];

            if(targBlock.posX<0||targBlock.posY<0||
               targBlock.posX>=terrain.size()||targBlock.posY>=terrain.size())break;

            if(centerI!=targI)
            {
                cellx=X+targBlock.posX-centerBlock.posX;
                celly=Y+targBlock.posY-centerBlock.posY;
                if(cellx<0||celly<0||
                        cellx>=terrain.size()||celly>=terrain.size())
                {
                    associated=false;
                    break;
                }

                Cellule targCell=terrain[cellx][celly];
                bool oneCorrespond=false;
                for(int numI=0;numI<targCell.objects.size();numI++)
                {

                    Object targObject=targCell.objects[numI];

                    if(targObject.state==targBlock.state&&
                       targObject.type==targBlock.type)
                    {
                        oneCorrespond=true;
                        break;
                    }
                }
                if(!oneCorrespond)
                {
                    associated=false;
                    break;
                }
            }
        }
        if(associated)
        {
            return true;
        }
    }
    return false;
}*/
#define for_each(VAR,LIST) for(int VAR=0; VAR<LIST.size(); VAR++)
bool Terrain::_ifCorrespond(AssociateBlock &block,int &X,int &Y,int &NUM)
{
    Object ctrobj=terrain[X][Y].objects[NUM];

    for_each(i,block.type)
    if(block.type[i]==ctrobj.type)
    {
        for_each(y,block.state)
            if(block.state[y]==ctrobj.state)
                return true;
        break;
    }
    return false;
}
bool Terrain::ifCorrespond(AssociateBlock &block,int X,int Y,int NUM)
{
    if(X<0||Y<0||X>=terrain.size()||Y>=terrain.size())return false;
    return _ifCorrespond(block,X,Y,NUM);
}
bool Terrain::ifCorrespond(AssociateBlock &block,int X,int Y)
{
    if(X<0||Y<0||X>=terrain.size()||Y>=terrain.size())return false;
    for_each(NUM,terrain[X][Y].objects)
    {
        if(_ifCorrespond(block,X,Y,NUM)){return true;}
    }

    return false;
}
bool Terrain::ifAssociateWith(Association &association,int X,int Y,int NUM)
{
    Object ctrobj=terrain[X][Y].objects[NUM];
    int cellx,celly;

    //FOR EACH BLOCK
    for_each(centI,association.blocks)
    if(ifCorrespond(association.blocks[centI],X,Y,NUM))
    {
        bool associate=true;
        AssociateBlock &centBk=association.blocks[centI];
        for_each(targI,association.blocks)
        {
            AssociateBlock &targBk=association.blocks[targI];
            cellx=X+targBk.posX-centBk.posX;
            celly=Y+targBk.posY-centBk.posY;

            if(!ifCorrespond(targBk,cellx,celly))
            {
                associate=false;
                break;
            }
        }
        if(associate)return true;
    }
    return false;
    /*if(centerObject.state==association.blocks[centerI].state&&
       centerObject.type==association.blocks[centerI].type)
    {
        AssociateBlock centerBlock=association.blocks[centerI];
        bool associated=true;

        for(int targI=0;targI<association.blocks.size();targI++)
        {
            AssociateBlock targBlock=association.blocks[targI];

            if(targBlock.posX<0||targBlock.posY<0||
               targBlock.posX>=terrain.size()||targBlock.posY>=terrain.size())break;

            if(centerI!=targI)
            {
                cellx=X+targBlock.posX-centerBlock.posX;
                celly=Y+targBlock.posY-centerBlock.posY;
                if(cellx<0||celly<0||
                        cellx>=terrain.size()||celly>=terrain.size())
                {
                    associated=false;
                    break;
                }

                Cellule targCell=terrain[cellx][celly];
                bool oneCorrespond=false;
                for(int numI=0;numI<targCell.objects.size();numI++)
                {

                    Object targObject=targCell.objects[numI];

                    if(targObject.state==targBlock.state&&
                       targObject.type==targBlock.type)
                    {
                        oneCorrespond=true;
                        break;
                    }
                }
                if(!oneCorrespond)
                {
                    associated=false;
                    break;
                }
            }
        }
        if(associated)
        {
            return true;
        }
    }*/
}
bool Terrain::ifAssociate(int X,int Y,int NUM)
{
    for(int i=0;i<content::associations.size();i++)
    {
        if(ifAssociateWith(content::associations[i],X,Y,NUM))return true;
    }
    return false;
}
