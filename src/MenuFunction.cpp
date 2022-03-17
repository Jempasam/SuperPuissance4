#include "MenuFunction.h"
namespace global
{
    int selectedMenu=-1;
}

void useMenuObject(sf::RenderTarget &TARGET, MenuObject &mobject, Terrain &terrain)
{
    ScriptTarget target;
    drawTex(TARGET,
            *mobject.textures[treatArg(mobject.texNum,target,terrain)],
            treatArg(mobject.X1,target,terrain),treatArg(mobject.Y1,target,terrain),
            treatArg(mobject.X2,target,terrain),treatArg(mobject.Y2,target,terrain)
            );
}
void useMenu(sf::RenderTarget &TARGET, Menu &menu, Terrain &terrain)
{
    for(int i=0;i<menu.objects.size();i++)
    {
        useMenuObject(TARGET,menu.objects[i],terrain);
    }
}
void treatMenu(sf::RenderTarget &TARGET, Terrain &terrain)
{
    if(global::selectedMenu!=-1)
    {
        useMenu(TARGET,content::menus[global::selectedMenu],terrain);
    }
}
