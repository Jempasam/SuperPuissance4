#include "../include/content.h"

namespace global
{
    int maxTimer=0;
}

namespace content
{
    std::vector<ObjectType> objectType;
    std::vector<ObjectState> objectState;
    std::vector<TerrainSkin> terrainSkin;
    std::vector<SpawnerHand> spawnerHand;
    std::vector<Team> teams;
    std::vector<KeyConfig> keyConfig;
    std::vector<Association> associations;
    std::vector<Menu> menus;

    std::vector<ID> ids;
    std::vector<Tag> tags;

    std::vector<GlobalVariable> globalVar;

    std::list<sf::Texture> textures;
}
Vector2::Vector2()
{
    x=0;y=0;
}
Vector2::Vector2(int X,int Y)
{
    x=X;y=Y;
}
intColor::intColor()
{
    r=0;g=0;b=0;a=0;
}
intColor::intColor(int R,int G,int B,int A)
{
    r=R;g=G;b=B;a=A;
}
intColor &intColor::operator=(intColor color)
{
    a=color.a;
    r=color.r;
    g=color.g;
    b=color.b;

    return *this;
}
SquareZone::SquareZone()
{
    b1=Vector2();b2=Vector2();
}
SquareZone::SquareZone(Vector2 border1,Vector2 border2)
{
    b1=border1;b2=border2;
}
bool SquareZone::isInZone(int X,int Y)
{
    if((X>=b1.x||b1.x==-1)&&(X<=b2.x||b2.x==-1)&&(Y>=b1.y||b1.y==-1)&&(Y<=b2.y||b2.y==-1))return true;
    else return false;
}
bool ComplexZone::isInZone(int X,int Y)
{
    for(int i=0;i<squares.size();i++)
    {
        if(squares[i].isInZone(X,Y))return true;
    }
    return false;
}
