#include "ScriptFunction.h"
int compOperatorToInt(std::string OPERATOR)
{
    if(OPERATOR=="=")return 0;
    else if(OPERATOR==">")return 1;
    else if(OPERATOR=="<")return 2;
    else if(OPERATOR=="!=")return 3;
    else if(OPERATOR==">=")return 4;
    else if(OPERATOR=="<=")return 5;
}
Argument compOperatorToArgument(std::string OPERATOR)
{

    Argument argument;Value newValue;
    newValue.type=ArgumentType::value;
    newValue.operat=ArgOperator::plus;

    if(OPERATOR=="=")newValue.value.push_back(0);
    else if(OPERATOR==">")newValue.value.push_back(1);
    else if(OPERATOR=="<")newValue.value.push_back(2);
    else if(OPERATOR=="!=")newValue.value.push_back(3);
    else if(OPERATOR==">=")newValue.value.push_back(4);
    else if(OPERATOR=="<=")newValue.value.push_back(5);

    argument.values.push_back(newValue);

    return argument;
}
int variableToInt(std::string VARIABLE)
{
    if(VARIABLE=="Type")return 0;
    else if(VARIABLE=="State")return 1;
    else if(VARIABLE=="Case")return 2;
    else if(VARIABLE=="ObjectNumber")return 3;
    else if(VARIABLE=="ccc")return 4;
    else if(VARIABLE=="ccc")return 5;
}
std::string intToCompOperator(int INT)
{
    if(INT==0)return "=";
    else if(INT==1)return ">";
    else if(INT==2)return "<";
    else if(INT==3)return "!=";
    else if(INT==4)return ">=";
    else if(INT==5)return "<=";
}
bool compare(int value1,int OPERATOR,int value2)
{
    if(OPERATOR==0){if(value1==value2)return true;}
    else if(OPERATOR==1){if(value1>value2)return true;}
    else if(OPERATOR==2){if(value1<value2)return true;}
    else if(OPERATOR==3){if(value1!=value2)return true;}
    else if(OPERATOR==4){if(value1>=value2)return true;}
    else if(OPERATOR==5){if(value1<=value2)return true;}
    return true;
}
bool compare(std::vector<int> &values1,int OPERATOR,std::vector<int> &values2,ScriptTarget &target)
{
    for(int i=0;i<values1.size();i++)
    for(int y=0;y<values2.size();y++)
    {
        if(OPERATOR==0){if(values1[i]==values2[y])return true;}
        else if(OPERATOR==1){if(values1[i]>values2[y])return true;}
        else if(OPERATOR==2){if(values1[i]<values2[y])return true;}
        else if(OPERATOR==3){if(values1[i]!=values2[y])return true;}
        else if(OPERATOR==4){if(values1[i]>=values2[y])return true;}
        else if(OPERATOR==5){if(values1[i]<=values2[y])return true;}
    }
    return false;
}
bool compare(int &value1,int OPERATOR,Argument &value2,ScriptTarget &target,Terrain &terrain)
{
    std::vector<int> values1,values2;
    values2=vecTreatArg(value2,target,terrain);
    values1.push_back(value1);

    return compare(values1,OPERATOR,values2,target);
}
bool compare(Argument &value1,int OPERATOR,Argument &value2,ScriptTarget &target,Terrain &terrain)
{
    std::vector<int> values1,values2;
    values1=vecTreatArg(value1,target,terrain);
    values2=vecTreatArg(value2,target,terrain);
    return compare(values1,OPERATOR,values2,target);
}
void useModifiers(std::vector<Modifier> &modifiers,ScriptTarget &target,Terrain &terrain)
{
    for(int i=0;i<modifiers.size();i++)
    {
        switch(modifiers[i].type)
        {
            case ModifierType::pos1:{
                target.X=treatArg(modifiers[i].arguments[0],target,terrain);
                target.Y=treatArg(modifiers[i].arguments[1],target,terrain);
                break;
            }
            case ModifierType::offset1:{
                target.X=target.X+treatArg(modifiers[i].arguments[0],target,terrain);
                target.Y=target.Y+treatArg(modifiers[i].arguments[1],target,terrain);
                break;
            }
            case ModifierType::num1:{
                target.NUM=treatArg(modifiers[i].arguments[0],target,terrain);
                break;
            }
            case ModifierType::team1:{
                target.TEAM=treatArg(modifiers[i].arguments[0],target,terrain);
                break;
            }
        }
    }
}
std::vector<int> vecTreatArg(Argument &argument,ScriptTarget target,Terrain &terrain)
{
    target.reset();
    std::vector<int> RETURN,OLDRETURN;
    for(int i=0;i<argument.values.size();i++)
    {
        if(argument.values[i].operat==ArgOperator::elementstart)
        {
            OLDRETURN=RETURN;
            RETURN.clear();
            i++;
        }
        else if(argument.values[i].operat==ArgOperator::elementend)
        {

            std::vector<int> newReturn;
            for(int i=0;i<RETURN.size();i++)
            {
                newReturn.push_back(OLDRETURN[RETURN[i]]);
            }
            RETURN=newReturn;
            i++;
        }
        if(i>=argument.values.size())break;

        std::vector<int> VALUE;

        useModifiers(argument.values[i].modifiers,target,terrain);


        switch(argument.values[i].type)
        {
            case ArgumentType::value:{
                for(int y=0;y<argument.values[i].value.size();y++)
                        VALUE.push_back(argument.values[i].value[y]);
                break;
            }

            case ArgumentType::tag:{
                for(int y=0;y<content::tags[argument.values[i].value[0]].nums.size();y++)
                {
                    VALUE.push_back(content::tags[argument.values[i].value[0]].nums[y]);
                }
                break;
            }

            case ArgumentType::var:{
                Object &objTarget=terrain.terrain[target.X][target.Y].objects[target.NUM];

                while(argument.values[i].value[0]>=objTarget.variables.size())
                {
                    objTarget.variables.push_back(0);
                }
                VALUE.push_back(objTarget.variables[argument.values[i].value[0]]);
                break;
            }

            case ArgumentType::objectvar:{
                Object &objTarget=terrain.terrain[target.X][target.Y].objects[target.NUM];

                VALUE.push_back(content::objectType[objTarget.type].variables[argument.values[i].value[0]]);
                break;
            }
            case ArgumentType::dynamic:{
                Cellule &celTarget=terrain.terrain[target.X][target.Y];
                switch(argument.values[i].value[0])
                {
                    case 0:{//STATE
                        VALUE.push_back(celTarget.objects[target.NUM].state);
                        break;
                    }
                    case 1:{//STATES
                        for(int y=0;y<celTarget.objects.size();y++)
                                        VALUE.push_back(celTarget.objects[y].state);
                        break;
                    }
                    case 2:{//TYPE
                        VALUE.push_back(celTarget.objects[target.NUM].type);
                        break;
                    }
                    case 3:{//TYPES
                        for(int y=0;y<celTarget.objects.size();y++)
                                        VALUE.push_back(celTarget.objects[y].type);
                        break;
                    }
                    case 4:{//CURSORX
                        for(int y=0;y<celTarget.objects.size();y++)
                                        VALUE.push_back(content::teams[target.TEAM].cursorPos.x);
                        break;
                    }
                    case 5:{//CURSORY
                        for(int y=0;y<celTarget.objects.size();y++)
                                        VALUE.push_back(content::teams[target.TEAM].cursorPos.y);
                        break;
                    }
                    case 6:{//TIMER
                        for(int y=0;y<celTarget.objects.size();y++)
                                        VALUE.push_back(celTarget.objects[target.NUM].timer);
                        break;
                    }
                    case 7:{//CGROUP
                        for(int y=0;y<celTarget.objects.size();y++)
                                        VALUE.push_back(celTarget.objects[target.NUM].cGroup);
                        break;
                    }
                    case 8:{//WORLDSIZEX
                        VALUE.push_back(terrain.terrain.size());
                        break;
                    }
                    case 9:{//WORLDSIZEY
                        VALUE.push_back(terrain.terrain[0].size());
                        break;
                    }
                    case 10:{//WINDOWWIDTH
                        VALUE.push_back(global::wWidth);
                        break;
                    }
                    case 11:{//WINDOWHEIGHT
                        VALUE.push_back(global::wHeight);
                        break;
                    }
                    case 12:{//DIDASSOCIATE
                        VALUE.push_back(terrain.ifAssociate(target.X,target.Y,target.NUM));
                        break;
                    }
                    case 13:{//ISOUTSIDE
                        VALUE.push_back((target.X<0||target.Y<0||target.X>=terrain.terrain.size()||target.Y>=terrain.terrain[0].size()));
                        break;
                    }
                }
                break;
            }
        }
        target.reset();

        if(argument.values[i].operat!=ArgOperator::pushback)
        {
            if(VALUE.size()>=RETURN.size())
            {
                for(int y=RETURN.size();y<VALUE.size();y++)
                {
                    if(RETURN.size()>0)RETURN.push_back(RETURN[RETURN.size()-1]);
                    else RETURN.push_back(0);
                }
            }
            if(RETURN.size()>=VALUE.size())
            {
                for(int y=VALUE.size();y<RETURN.size();y++)
                {
                    if(VALUE.size()>0)VALUE.push_back(VALUE[VALUE.size()-1]);
                    else VALUE.push_back(0);
                }
            }
        }
        for(int y=0;y<VALUE.size();y++)
        {
            if(argument.values[i].operat==ArgOperator::plus)RETURN[y]+=VALUE[y];
            if(argument.values[i].operat==ArgOperator::minus)RETURN[y]-=VALUE[y];
            if(argument.values[i].operat==ArgOperator::multiply)RETURN[y]*=VALUE[y];
            if(argument.values[i].operat==ArgOperator::divide)RETURN[y]/=VALUE[y];
            if(argument.values[i].operat==ArgOperator::pushback)RETURN.push_back(VALUE[y]);
            if(argument.values[i].operat==ArgOperator::et)RETURN[y]=(RETURN[y]&&VALUE[y]);
            if(argument.values[i].operat==ArgOperator::ou)RETURN[y]=(RETURN[y]||VALUE[y]);
            if(argument.values[i].operat==ArgOperator::xou)RETURN[y]=((RETURN[y]||VALUE[y])&&!(RETURN[y]&&VALUE[y]));
        }
    }
    return RETURN;
}
int treatArg(Argument &argument,ScriptTarget &target,Terrain &terrain)
{
    std::vector<int> RETURNS=vecTreatArg(argument,target,terrain);

    if(RETURNS.size()==0)return -134568;
    else return RETURNS[getRandomNumber(RETURNS.size()-1)];
}
bool useFScript(std::vector<long> &script)
{
    std::vector<long>::iterator i=script.begin();
    while(i!=script.end())
    {
        switch(*i)
        {
            case 0:{//SET A B : A=B
                i++;
                *reinterpret_cast<long*>(*i)=*reinterpret_cast<long*>(*(i+1));
                i++;
                break;
            }
            case 1:{//ADD A B : A+=B
                i++;
                *reinterpret_cast<long*>(*i)+=*reinterpret_cast<long*>(*(i+1));
                i++;
                break;
            }
            case 2:{//ADD A B : A-=B
                i++;
                *reinterpret_cast<long*>(*i)-=*reinterpret_cast<long*>(*(i+1));
                i++;
                break;
            }
            case 3:{//ADD A B : A*=B
                i++;
                *reinterpret_cast<long*>(*i)*=*reinterpret_cast<long*>(*(i+1));
                i++;
                break;
            }
            case 4:{//ADD A B : A/=B
                i++;
                *reinterpret_cast<long*>(*i)/=*reinterpret_cast<long*>(*(i+1));
                i++;
                break;
            }
            case 5:{//SET A B : A=NUM
                i++;
                *reinterpret_cast<long*>(*i)=*(i+1);
                i++;
                break;
            }
            case 6:{//ADD A B : A+=NUM
                i++;
                *reinterpret_cast<long*>(*i)+=*(i+1);
                i++;
                break;
            }
            case 7:{//ADD A B : A-=NUM
                i++;
                *reinterpret_cast<long*>(*i)-=*(i+1);
                i++;
                break;
            }
            case 8:{//ADD A B : A*=NUM
                i++;
                *reinterpret_cast<long*>(*i)*=*(i+1);
                i++;
                break;
            }
            case 9:{//ADD A B : A/=NUM
                i++;
                *reinterpret_cast<long*>(*i)/=*(i+1);
                i++;
                break;
            }
            case 10:{//GOTO A
                i=script.begin()+*reinterpret_cast<long*>(*(i+1))-1;
                break;
            }
            case 11:{//GOTO NUM
                i=script.begin()+*(i+1)-1;
                break;
            }
            case 12:{//IF A GOTO NUM
                if(*i+1)i=script.begin()+*(i+2)-1;
                else i+2;
                break;
            }
            case 13:{//IF A GOTO NUM
                if(!*i+1)i=script.begin()+*(i+2)-1;
                else i+2;
                break;
            }
        }
        i++;
    }
}
bool useCGroup(sf::RenderTexture &TARGET,Terrain &terrain,ScriptTarget &target,CommandGroup &cgroup,int &timer,int &cGroup)
{
    for(int i=0;i<cgroup.commands.size();i++)
    {
        Command &COMMAND=cgroup.commands[i];
        useModifiers(COMMAND.modifiers,target,terrain);
        bool BREAK=false;
        //std::cout<<"<||"<<COMMAND.command<<"||>\n";
        switch(COMMAND.command)
        {

            case command::move:{
                terrain.moveObject(TARGET,target.X,target.Y,target.NUM,target.X+treatArg(COMMAND.argument[0],target,terrain),target.Y+treatArg(COMMAND.argument[1],target,terrain));
                BREAK=true;
                break;
            }

            case command::breek:{
                BREAK=true;
                break;
            }

            case command::setpos:{
                terrain.moveObject(TARGET,target.X,target.Y,target.NUM,treatArg(COMMAND.argument[0],target,terrain),treatArg(COMMAND.argument[1],target,terrain));
                BREAK=true;
                break;
            }

            case command::ifObject:{
                Object &objTarget=terrain.terrain[target.X][target.Y].objects[target.NUM];
                if(!compare(objTarget.type,COMMAND.argument[0].values[0].value[0],COMMAND.argument[1],target,terrain))
                {
                    i+=treatArg(COMMAND.argument[2],target,terrain)-1;
                }
                break;
            }

            case command::ifState:{

                Object &objTarget=terrain.terrain[target.X][target.Y].objects[target.NUM];
                if(!compare(objTarget.type,COMMAND.argument[0].values[0].value[0],COMMAND.argument[1],target,terrain))
                {
                    i+=treatArg(COMMAND.argument[2],target,terrain)-1;
                }
                break;
            }

            case command::usefunction:{

                Object &objTarget=terrain.terrain[target.X][target.Y].objects[target.NUM];

                ScriptTarget newtarg=target;
                newtarg.TYPEbase=newtarg.TYPE; newtarg.TEAMbase=newtarg.TEAM; newtarg.NUMbase=newtarg.NUM;
                newtarg.Xbase=newtarg.X; newtarg.Ybase=newtarg.Y;
                useCGroup(TARGET,terrain,target,
                          content::functions[treatArg(COMMAND.argument[0],newtarg,terrain)],
                          timer,cGroup);
                break;
            }

            case command::ifOneObject:{
                if(target.X<0||target.Y<0||target.X>=terrain.terrain.size()||target.Y>=terrain.terrain[0].size())
                {
                    i+=treatArg(COMMAND.argument[2],target,terrain)-1;
                }
                else
                {
                    Cellule &celTarget=terrain.terrain[target.X][target.Y];

                    bool oneTrue=false;
                    for(int i=0;i<celTarget.objects.size();i++)
                    if(!compare(celTarget.objects[i].type,COMMAND.argument[0].values[0].value[0],COMMAND.argument[1],target,terrain))
                    {
                        oneTrue=true;
                        break;
                    }

                    if(!oneTrue)i+=treatArg(COMMAND.argument[2],target,terrain)-1;
                }
                break;
            }

            case command::ifall:{
                std::cout<<"|"<<treatArg(COMMAND.argument[0],target,terrain)<<"|"<<treatArg(COMMAND.argument[2],target,terrain)<<"|";
                if(!compare(COMMAND.argument[0],COMMAND.argument[1].values[0].value[0],COMMAND.argument[2],target,terrain))
                {
                    i+=treatArg(COMMAND.argument[3],target,terrain)-1;
                }
                break;
            }

            case command::ifOneState:{
                if(target.X<0||target.Y<0||target.X>=terrain.terrain.size()||target.Y>=terrain.terrain[0].size())
                {
                    i+=treatArg(COMMAND.argument[2],target,terrain)-1;
                }
                else
                {
                    Cellule &celTarget=terrain.terrain[target.X][target.Y];

                    bool oneTrue=false;
                    for(int i=0;i<celTarget.objects.size();i++)
                    if(compare(celTarget.objects[i].state,COMMAND.argument[0].values[0].value[0],COMMAND.argument[1],target,terrain))
                    {
                        oneTrue=true;
                        break;
                    }
                    if(!oneTrue)i+=treatArg(COMMAND.argument[2],target,terrain)-1;
                }
                break;
            }

            case command::ifSomeoneKeyPressed:{
                    bool oneTrue=false;
                    for(int i=0;i<content::keyConfig.size();i++)
                    {
                        if(sf::Keyboard::isKeyPressed(content::keyConfig[i].customKeys[treatArg(COMMAND.argument[0],target,terrain)]))
                        {
                            oneTrue=true;
                            break;
                        }
                    }
                    if(!oneTrue)i+=treatArg(COMMAND.argument[1],target,terrain)-1;
                break;
            }

            case command::ifKeyPressed:{
                if(!sf::Keyboard::isKeyPressed(content::keyConfig[target.TEAM].customKeys[treatArg(COMMAND.argument[0],target,terrain)]))
                {
                    i+=treatArg(COMMAND.argument[1],target,terrain)-1;
                }
                break;
            }
            case command::setObject:{
                Object &objTarget=terrain.terrain[target.X][target.Y].objects[target.NUM];
                objTarget.type=treatArg(COMMAND.argument[0],target,terrain);
                break;
            }

            case command::setmenu:{
                std::cout<<"poulpe";
                global::selectedMenu=treatArg(COMMAND.argument[0],target,terrain);
                break;
            }

            case command::setState:{

                Object &objTarget=terrain.terrain[target.X][target.Y].objects[target.NUM];
                objTarget.state=treatArg(COMMAND.argument[0],target,terrain);
                objTarget.timer=0;objTarget.cGroup=0;
                objTarget.stateTex=0;
                terrain.drawObjectAt(TARGET,target.X,target.Y);
            }
            case command::setObjectTex:{
                Object &objTarget=terrain.terrain[target.X][target.Y].objects[target.NUM];
                objTarget.objectTex=treatArg(COMMAND.argument[0],target,terrain);
                break;
            }
            case command::setStateTex:{
                Object &objTarget=terrain.terrain[target.X][target.Y].objects[target.NUM];
                objTarget.stateTex=treatArg(COMMAND.argument[0],target,terrain);
                break;
            }

            case command::settimer:{
                Object &objTarget=terrain.terrain[target.X][target.Y].objects[target.NUM];
                objTarget.timer=treatArg(COMMAND.argument[0],target,terrain);
                break;
            }

            case command::setcgroup:{
                Object &objTarget=terrain.terrain[target.X][target.Y].objects[target.NUM];
                objTarget.cGroup=treatArg(COMMAND.argument[0],target,terrain);
                break;
            }

            case command::variableset:{
                Object &objTarget=terrain.terrain[target.X][target.Y].objects[target.NUM];

                while(COMMAND.argument[0].values[0].value[0]>=objTarget.variables.size())
                {
                    objTarget.variables.push_back(0);
                }
                objTarget.variables[COMMAND.argument[0].values[0].value[0]]=treatArg(COMMAND.argument[1],target,terrain);

                break;
            }
            case command::ifOneOutside:{
                if(target.X<0||target.Y<0||target.X>=terrain.terrain.size()||target.Y>=terrain.terrain[0].size())
                {
                }
                else
                {
                    i+=treatArg(COMMAND.argument[0],target,terrain)-1;
                }
                break;
            }
            case command::ifOneInside:{
                if(target.X<0||target.Y<0||target.X>=terrain.terrain.size()||target.Y>=terrain.terrain[0].size())
                {
                    i+=treatArg(COMMAND.argument[0],target,terrain)-1;
                }
                break;
            }

        }
        target.reset();
        if(BREAK)
        {
            break;
        }
    }
}
bool useScript(sf::RenderTexture &TARGET,Terrain &terrain,ScriptTarget target,Script &script,int &timer,int &cGroup)
{
    CommandGroup &commandGroup=script.commandGroup[cGroup];

    timer++;
    if(timer>=commandGroup.duration)
    {
        timer=0;
        cGroup++;
        if(cGroup>=script.commandGroup.size())
            cGroup=0;
    }
    target.reset();
    useCGroup(TARGET,terrain,target,commandGroup,timer,cGroup);
}
void useScriptAt(sf::RenderTexture &TARGET,int X,int Y,int objectNum,Terrain &terrain,int scriptNum)
{
    ScriptTarget target;
    target.Xbase=X; target.Ybase=Y; target.NUMbase=objectNum;
    target.TEAMbase=terrain.terrain[X][Y].objects[objectNum].player;
    target.identifier=terrain.terrain[X][Y].objects[objectNum].identifier;
    Object &object=terrain.terrain[X][Y].objects[objectNum];

    useScript(TARGET,terrain,target,content::scripts[scriptNum],object.timer,object.cGroup);
}

void treatScriptAt(sf::RenderTexture &TARGET,int X,int Y,Terrain &terrain)
{
    int numMax=terrain.terrain[X][Y].objects.size();
    for(int objI=0;objI<terrain.terrain[X][Y].objects.size();objI++)
    {

        if(terrain.terrain[X][Y].objects.size()<numMax)
        {
            numMax=terrain.terrain[X][Y].objects.size();
            objI-=numMax-terrain.terrain[X][Y].objects.size();
            if(objI<0)objI=0;
        }
        int scriptNum=content::objectState[terrain.terrain[X][Y].objects[objI].state].script;
        bool &treatedFrame=terrain.terrain[X][Y].objects[objI].treatedFrame;

        if(treatedFrame!=terrain.terrain_treatedFrame)
        {
            treatedFrame=terrain.terrain_treatedFrame;
            useScriptAt(TARGET,X,Y,objI,terrain,scriptNum);
        }
    }
}
void treatScript(sf::RenderTexture &TARGET,Terrain &terrain)
{
    if(terrain.terrain_treatedFrame)terrain.terrain_treatedFrame=false;
    else terrain.terrain_treatedFrame=true;

    for(int y=0;y<terrain.terrain[0].size();y++)
    {
        for(int x=0;x<terrain.terrain.size();x++)
        {
            treatScriptAt(TARGET,x,y,terrain);
        }
    }
}
