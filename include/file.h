#ifndef FILE_H
#define FILE_H

#include "../include/content.h"
#include "Utility.h"
#include "ScriptFunction.h"
#include "Terrain.h"
#include <fstream>
#include <iostream>
#include "cstdlib"
#include <SFML/Graphics.hpp>

struct LoadVariable
{
    std::string tag;
    std::string value;
};

namespace file
{
    extern std::vector<LoadVariable> loadvariables;
    extern std::vector<ID> definition;
}

int treatValue(std::string LINE);
std::vector<int> vecTreatValue2(std::string LINE,std::vector<std::string> &variables);
std::vector<int> vecTreatValue3(std::string LINE,std::vector<std::string> &variables);
std::vector<int> vecTreatValue(std::string LINE);
Argument treatAIValue(std::string LINE,std::vector<std::string> &variables);
Argument treatAIValue(std::string LINE);
void loadContentFile(std::string filename,std::string contentname="");
void loadContent(std::string contentname);
sf::Texture* createTexture(std::ifstream &file,std::string contentname);
bool getWord(std::ifstream &file,std::string &WORD, std::string SEPARATOR, std::string WORDCHAR="", std::string EXCLUSIONSTART="", std::string EXCLUSIONEND="");
std::string getWordReturn(std::ifstream &file,std::string SEPARATOR,std::string WORDCHAR,std::string EXCLUSIONSTART="",std::string EXCLUSIONEND="");



#endif // FILE_H
