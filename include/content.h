#ifndef CONTENT_H
#define CONTENT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "Script.h"

namespace global
{
    extern int maxTimer;
}
struct Color
{
    char r;
    char g;
    char b;
};
struct ID
{
    std::string text;
    int num;
    ID(const int &m_num, const std::string &m_text): text(m_text)
    {
        num=m_num;
    }
    ID()
    {

    }
};
struct GlobalVariable
{
    std::string text;
    Argument value;
};
struct Tag
{
    std::vector<int> nums;
};
struct ObjectType
{
    std::vector<sf::Texture*> textures;
    int tag;
    std::vector<int> variables;
};

struct ObjectState
{
    std::vector<sf::Texture*> textures;
    int script;
    sf::Color color;
    int texIconNumber;

};

struct TerrainSkin
{
    std::vector<sf::Texture*> textures;
    sf::Texture* background;
    sf::Texture* pannel;
    sf::Texture* bar;
    sf::Texture* selector;
};

struct Vector2
{
    int x,y;
    Vector2();
    Vector2(int X,int Y);
};
struct intColor
{
    int r,g,b,a;

    intColor();
    intColor(int R,int G,int B,int A);

    intColor &operator=(intColor color);
};
struct SquareZone
{
    Vector2 b1,b2;
    SquareZone();
    SquareZone(Vector2 border1,Vector2 border2);
    bool isInZone(int X,int Y);
};
struct ComplexZone
{
    std::vector<SquareZone> squares;
    bool isInZone(int X,int Y);
};
struct Spawner
{
    ComplexZone zone;
    int state;
    int object;
    int timer;
    sf::Texture cursorZone;
};
struct SpawnerHand
{
    std::vector<std::vector<Spawner>> spawner;
    std::vector<intColor> colorsOffset;
};
struct Team
{
    sf::Color color;
    int timer;
    int spawnerHand;

    int selectedCategory,selectedSpawner;
    Vector2 cursorPos;

    sf::Texture* cursorTex;
    sf::Texture* cursor2Tex;
};
struct KeyConfig
{
    sf::Keyboard::Key up=sf::Keyboard::Unknown;
    sf::Keyboard::Key down=sf::Keyboard::Unknown;
    sf::Keyboard::Key left=sf::Keyboard::Unknown;
    sf::Keyboard::Key right=sf::Keyboard::Unknown;

    sf::Keyboard::Key spawnNext=sf::Keyboard::Unknown;
    sf::Keyboard::Key spawnPrevious=sf::Keyboard::Unknown;

    sf::Keyboard::Key categoryNext=sf::Keyboard::Unknown;
    sf::Keyboard::Key categoryPrevious=sf::Keyboard::Unknown;

    sf::Keyboard::Key createObject=sf::Keyboard::Unknown;

    std::vector<sf::Keyboard::Key> customKeys;
};
struct AssociateBlock
{
    int posX=0,posY=0;
    std::vector<int> state;
    std::vector<int> type;
};
struct Association
{
    std::vector<AssociateBlock> blocks;
    std::vector<int> states;
    std::vector<int> type;
    Association(): blocks(),states(),type()
    {
    }
    Association(const Association &b): blocks(b.blocks),states(b.states),type(b.type)
    {
    }
};

enum MenuObjectType
{
    picture=0,
    button=1
};
struct MenuObject
{
    int script;
    MenuObjectType type;
    int typeOption;
    std::vector<sf::Texture*> textures;
    Argument texNum;
    Argument X1,Y1;
    Argument X2,Y2;
};
struct Menu
{
    std::vector<MenuObject> objects;
};

namespace content
{
    extern std::vector<ObjectType> objectType;
    extern std::vector<ObjectState> objectState;
    extern std::vector<TerrainSkin> terrainSkin;
    extern std::vector<SpawnerHand> spawnerHand;
    extern std::vector<Team> teams;
    extern std::vector<KeyConfig> keyConfig;
    extern std::vector<Association> associations;
    extern std::vector<Menu> menus;

    extern std::vector<ID> ids;
    extern std::vector<Tag> tags;

    extern std::vector<GlobalVariable> globalVar;

    extern std::list<sf::Texture> textures;
}

#endif // CONTENT_H
