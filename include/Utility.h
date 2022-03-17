#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Graphics.h"

int CharToInt(char STRING);
int getRandomNumber(int maxNumber);
sf::Texture* getTexFromList(std::vector<sf::Texture*> &texList,int index);
int CharToInt2(char STRING);
char IntToChar(int NUM);
std::string IntToTerrainChars(int NUM);
int TerrainCharsToInt(std::string STR);
std::string IntToChars(int NUM);
std::string IntToUnit(int NUM);
std::string IntToString(int INT);
int StringToInt(std::string STRING);
std::string AddZero(int NUM,int TYPE);
std::vector<std::string> explode(std::string STRING,std::string SEPARATOR,std::string WORDSEP="",std::string exceptionstart="",std::string exceptionend="",bool KEEP_SEP=false,bool KEEP_EMPTY=true);
std::string getFrom(std::string STRING,int start,int end=-1);
std::string getFromChar(std::string STRING,char start,char end);

#endif // UTILITY_H
