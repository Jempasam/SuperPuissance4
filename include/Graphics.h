#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "content.h"

namespace global
{
    extern sf::RenderWindow window;
    extern sf::Texture nullTex;
    extern int wHeight;
    extern int wWidth;
    extern int mapXCoord;
}

void generateWindowConfig();
void regenerateWindowConfig(sf::RenderWindow &WINDOW);
void drawTex(sf::RenderTarget &TARGET,const sf::Texture &TEX,float X,float Y,float TX,float TY,int R=255,int G=255,int B=255,int Alpha=255);
void displaySelectedSpawner(sf::RenderWindow &WINDOW);
void eraseQuad(sf::RenderTarget &TARGET,float X,float Y,float TX,float TY);
void drawSquare(sf::RenderTarget &TARGET,float X,float Y,float TX,float TY,int R=255,int G=255,int B=255,int Alpha=255);

#endif // GRAPHICS_H
