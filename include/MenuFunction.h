#ifndef MENUFUNCTION_H
#define MENUFUNCTION_H

#include "content.h"
#include "ScriptFunction.h"
#include "Graphics.h"

namespace global
{
    extern int selectedMenu;
}

void useMenuObject(sf::RenderTarget &TARGET, MenuObject &mobject, Terrain &terrain);
void useMenu(sf::RenderTarget &TARGET, Menu &menu, Terrain &terrain);
void treatMenu(sf::RenderTarget &TARGET, Terrain &terrain);

#endif // MENUFUNCTION_H
