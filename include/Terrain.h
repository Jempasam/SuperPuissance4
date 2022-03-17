#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include "content.h"
#include "Script.h"
#include <SFML/Graphics.hpp>

struct Object
{
    bool treatedFrame=0;

    int player;

    int category=0;
    int type=0;
    int state=0;
    int timer=0;int cGroup=0;
    int objectTex=0;
    int stateTex=-2;
    intColor colorOffset;

    Object &operator=(Object object);
    Object();

    std::vector<int> variables;

    int identifier;
};

struct Cellule
{
    std::vector<Object> objects;
};

struct Terrain
{
    bool terrain_treatedFrame=0;
    std::vector< std::vector<Cellule> > terrain;
    int skin=0;
    std::vector<int> vecTreatArg(Argument &argument,ScriptTarget target);
    int treatArg(Argument &argument,ScriptTarget &target);
    void useModifiers(std::vector<Modifier> &modifiers,ScriptTarget &target);
    bool compare(std::vector<int> &values1,int OPERATOR,std::vector<int> &values2,ScriptTarget &target);
    bool compare(int &value1,int OPERATOR,Argument &value2,ScriptTarget &target);
    bool compare(Argument &value1,int OPERATOR,Argument &value2,ScriptTarget &target);
    bool ifCorrespond(AssociateBlock &block,int X,int Y,int NUM);
    bool ifCorrespond(AssociateBlock &block,int X,int Y);
    bool ifAssociateWith(Association &association,int X,int Y,int NUM);
    bool ifAssociate(int X,int Y,int NUM);
    void create(int X,int Y);
    void drawTerrain(sf::RenderTexture &TARGET);
    void drawObjects(sf::RenderTexture &TARGET);
    void drawObjectAt(sf::RenderTexture &TARGET,int X,int Y);
    void moveObject(sf::RenderTexture &TARGET,int X,int Y,int objectNum,int newX,int newY);
    void useScriptAt(sf::RenderTexture &TARGET,int X,int Y,int objectNum,int scriptNum);
    void treatScriptAt(sf::RenderTexture &TARGET,int X,int Y);
    void treatScript(sf::RenderTexture &TARGET);
    void drawCursor(sf::RenderTexture &TARGET);
    void drawCursorAt(sf::RenderTexture &TARGET,int X,int Y);
    void spawnObject(sf::RenderTexture &TARGET,int teamNumber,int X,int Y);
    void keyPressed(sf::RenderTexture &ObjMapTx,sf::RenderTexture &cursorTex,sf::Keyboard::Key key);
    void testKeyPressed(sf::RenderTexture &ObjMapTx,sf::RenderTexture &cursorTex);
    int getValueFromVariable(int VariableNum,int X,int Y,int objectNum);

private:
    bool _ifCorrespond(AssociateBlock &block,int &X,int &Y,int &NUM);
};

struct ArenaObject
{
    Argument X1,Y1;Argument X2,Y2;
    Argument posRandOffset;
    std::vector<Argument> objectTypes;
    std::vector<Argument> ObjectStates;
    Argument chanceToSpawn;
    int team=-1;

    bool typeStateSync=false;
    bool doClear=false;

    ArenaObject();
};
struct Arena
{
    std::vector<ArenaObject> objects;
};
namespace content
{
    extern std::vector<Arena> arenas;
}
namespace global
{
    extern Terrain terrain;
}
#endif // TERRAIN_H
