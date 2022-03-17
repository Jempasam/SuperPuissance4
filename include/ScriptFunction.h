#ifndef SCRIPTFUNCTION_H
#define SCRIPTFUNCTION_H

#include "Terrain.h"
#include "Script.h"
#include "Utility.h"
#include "TerrainFunction.h"
#include "Graphics.h"
#include "MenuFunction.h"

int compOperatorToInt(std::string OPERATOR);
Argument compOperatorToArgument(std::string OPERATOR);
std::string intToCompOperator(int INT);
bool compare(int value1,int OPERATOR,int value2);
std::vector<int> vecTreatArg(Argument &argument,ScriptTarget target,Terrain &terrain);
int treatArg(Argument &argument,ScriptTarget &target,Terrain &terrain);
void useScriptAt(sf::RenderTexture &TARGET,int X,int Y,int objectNum,Terrain &terrain,int scriptNum);
void treatScriptAt(sf::RenderTexture &TARGET,int X,int Y,Terrain &terrain);
void treatScript(sf::RenderTexture &TARGET,Terrain &terrain);

#endif // SCRIPTFUNCTION_H
