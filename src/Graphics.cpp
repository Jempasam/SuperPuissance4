#include "../include/Graphics.h"

namespace global
{
    sf::RenderWindow window;
    sf::Texture nullTex;
    int wHeight;
    int wWidth;
    int mapXCoord;
}

void generateWindowConfig()
{
    global::wHeight=sf::VideoMode::getDesktopMode().height/1.2;
    global::wWidth=sf::VideoMode::getDesktopMode().width/1.2;
    global::mapXCoord=(global::wWidth-global::wHeight)/2;
}
void regenerateWindowConfig(sf::RenderWindow &WINDOW)
{
    global::wHeight=WINDOW.getSize().y;
    global::wWidth=WINDOW.getSize().x;
    global::mapXCoord=(WINDOW.getSize().x-WINDOW.getSize().y)/2;
}
void drawTex(sf::RenderTarget &TARGET,const sf::Texture &TEX,float X,float Y,float TX,float TY,int R,int G,int B,int Alpha)
{
    sf::VertexArray SPRITE(sf::Quads,4);
    SPRITE[0].position=sf::Vector2f(X,Y);
    SPRITE[1].position=sf::Vector2f(X+TX,Y);
    SPRITE[2].position=sf::Vector2f(X+TX,Y+TY);
    SPRITE[3].position=sf::Vector2f(X,Y+TY);
    SPRITE[0].texCoords=sf::Vector2f(0,0);
    SPRITE[1].texCoords=sf::Vector2f(TEX.getSize().x,0);
    SPRITE[2].texCoords=sf::Vector2f(TEX.getSize().x,TEX.getSize().y);
    SPRITE[3].texCoords=sf::Vector2f(0,TEX.getSize().y);
    SPRITE[0].color=sf::Color(R,G,B,Alpha);
    SPRITE[1].color=sf::Color(R,G,B,Alpha);
    SPRITE[2].color=sf::Color(R,G,B,Alpha);
    SPRITE[3].color=sf::Color(R,G,B,Alpha);
    TARGET.draw(SPRITE,&TEX);
}
void eraseQuad(sf::RenderTarget &TARGET,float X,float Y,float TX,float TY)
{
    sf::VertexArray SPRITE(sf::Quads,4);
    SPRITE[0].position=sf::Vector2f(X,Y);
    SPRITE[1].position=sf::Vector2f(X+TX,Y);
    SPRITE[2].position=sf::Vector2f(X+TX,Y+TY);
    SPRITE[3].position=sf::Vector2f(X,Y+TY);
    SPRITE[0].color=sf::Color::Transparent;
    SPRITE[1].color=sf::Color::Transparent;
    SPRITE[2].color=sf::Color::Transparent;
    SPRITE[3].color=sf::Color::Transparent;
    TARGET.draw(SPRITE,sf::BlendNone);
}
void drawSquare(sf::RenderTarget &TARGET,float X,float Y,float TX,float TY,int R,int G,int B,int Alpha)
{
    sf::VertexArray SPRITE(sf::Quads,4);
    SPRITE[0].position=sf::Vector2f(X,Y);
    SPRITE[1].position=sf::Vector2f(X+TX,Y);
    SPRITE[2].position=sf::Vector2f(X+TX,Y+TY);
    SPRITE[3].position=sf::Vector2f(X,Y+TY);
    SPRITE[0].color=sf::Color(R,G,B,Alpha);
    SPRITE[1].color=sf::Color(R,G,B,Alpha);
    SPRITE[2].color=sf::Color(R,G,B,Alpha);
    SPRITE[3].color=sf::Color(R,G,B,Alpha);
    TARGET.draw(SPRITE);
}
void displaySelectedSpawner(sf::RenderWindow &WINDOW)
{
    for(int i=0;i<content::teams.size();i++)
    {
        int X,Y;
        if(i<3){X=global::wHeight*0.07;Y=global::wHeight*0.07+global::wHeight*0.27*i;}
        if(i>=3){X=global::wWidth-global::wHeight*0.27;Y=global::wHeight*0.07+global::wHeight*0.27*(i-3);}
        SpawnerHand &spawnerHand=content::spawnerHand[content::teams[i].spawnerHand];
        Spawner &spawner=spawnerHand.spawner[content::teams[i].selectedCategory][content::teams[i].selectedSpawner];
        sf::Texture &objectTex=*content::objectType[spawner.object].textures[0];
        sf::Color &color=content::objectState[spawner.state].color;

        sf::Color selecColor;
        selecColor.r=content::teams[i].color.r+spawnerHand.colorsOffset[content::teams[i].selectedCategory].r;
        selecColor.g=content::teams[i].color.g+spawnerHand.colorsOffset[content::teams[i].selectedCategory].g;
        selecColor.b=content::teams[i].color.b+spawnerHand.colorsOffset[content::teams[i].selectedCategory].b;
        selecColor.a=content::teams[i].color.a+spawnerHand.colorsOffset[content::teams[i].selectedCategory].a;

        drawTex(WINDOW,*content::terrainSkin[0].selector,
                X,Y,
                global::wHeight*0.20,global::wHeight*0.20,
                int(selecColor.r),int(selecColor.g),int(selecColor.b),int(selecColor.a));

        drawTex(WINDOW,objectTex,
                X+global::wHeight*0.031,Y+global::wHeight*0.031,
                global::wHeight*0.14,global::wHeight*0.14,
                int(color.r),int(color.g),int(color.b),int(color.a));

        if(content::objectState[spawner.state].textures.size()>0)
        drawTex(WINDOW,*content::objectState[spawner.state].textures[content::objectState[spawner.state].texIconNumber],
                X+global::wHeight*0.031,Y+global::wHeight*0.031,
                global::wHeight*0.14,global::wHeight*0.14,
                int(color.r),int(color.g),int(color.b),int(color.a));

        drawSquare(WINDOW,
                X+global::wHeight*0.031,Y+global::wHeight*0.031,
                (global::wHeight*0.14)*content::teams[i].timer/global::maxTimer,global::wHeight*0.14,
                int(selecColor.r),int(selecColor.g),int(selecColor.b),100);

    }
}
