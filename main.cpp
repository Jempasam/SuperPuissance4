#include <iostream>

#include "include/Graphics.h"
#include "Terrain.h"
#include "file.h"
#include "ScriptFunction.h"
#include "MenuFunction.h"

void displayMenu(sf::RenderTarget &TARGET,sf::RenderTexture &mapTex,sf::RenderTexture &objMapTex,sf::RenderTexture &cursorMapTex)
{
    drawTex(global::window,*content::terrainSkin[0].background,global::mapXCoord-global::wHeight,0,global::wHeight,global::wHeight);
    drawTex(global::window,*content::terrainSkin[0].background,global::mapXCoord+global::wHeight,0,global::wHeight,global::wHeight);

    drawTex(global::window,mapTex.getTexture(),global::mapXCoord,0,global::wHeight,global::wHeight);
    drawTex(global::window,objMapTex.getTexture(),global::mapXCoord,0,global::wHeight,global::wHeight);
    drawTex(global::window,cursorMapTex.getTexture(),global::mapXCoord,0,global::wHeight,global::wHeight);

    drawTex(global::window,*content::terrainSkin[0].bar,global::mapXCoord-global::wHeight*0.02,0,global::wHeight*0.02,global::wHeight);
    drawTex(global::window,*content::terrainSkin[0].bar,global::mapXCoord+global::wHeight,0,global::wHeight*0.02,global::wHeight);

    drawTex(global::window,*content::terrainSkin[0].pannel,0,0,global::wHeight*0.35,global::wHeight);
    drawTex(global::window,*content::terrainSkin[0].pannel,global::wWidth-global::wHeight*0.35,0,global::wHeight*0.35,global::wHeight);

    drawTex(global::window,*content::terrainSkin[0].bar,global::wHeight*0.34,0,global::wHeight*0.02,global::wHeight);
    drawTex(global::window,*content::terrainSkin[0].bar,global::wWidth-global::wHeight*0.36,0,global::wHeight*0.02,global::wHeight);
}
int main()
{
    std::ifstream file("start.ini");
    std::string line;
    std::getline(file,line);
    loadContent(line);
    file.close();

    if(content::arenas.size()>0)
        useArena(global::terrain,content::arenas[getRandomNumber(content::arenas.size()-1)]);

    global::selectedMenu=-1;

    generateWindowConfig();

    sf::RenderTexture mapT;global::terrain.drawTerrain(mapT);
    sf::RenderTexture objMapT;global::terrain.drawObjects(objMapT);

    sf::RenderTexture cursorMapT;global::terrain.drawCursor(cursorMapT);

    global::window.create(sf::VideoMode(global::wWidth,global::wHeight),"Puissance 4");

    bool keyAlreadyPressed=false;

    sf::Event event;
    sf::Clock clock;
    while(global::window.isOpen())
    {
        sf::sleep(sf::seconds(0.04-clock.getElapsedTime().asSeconds()));
        clock.restart();
        keyAlreadyPressed=false;
        while(global::window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                global::window.close();
            if (event.type == sf::Event::Resized)
            {
                global::window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                regenerateWindowConfig(global::window);
            }
            if (event.type == sf::Event::KeyPressed&&!keyAlreadyPressed)
            {
                if(global::selectedMenu==-1)global::terrain.keyPressed(objMapT,cursorMapT,event.key.code);
                global::terrain.drawCursor(cursorMapT);
                keyAlreadyPressed=true;
            }
        }
        treatScript(objMapT,global::terrain);

        displayMenu(global::window,mapT,objMapT,cursorMapT);

        displaySelectedSpawner(global::window);

        treatMenu(global::window,global::terrain);

        global::window.display();

        for(int i=0;i<content::teams.size();i++)
            {if(content::teams[i].timer>0)content::teams[i].timer--;}
    }


    return 0;
}
