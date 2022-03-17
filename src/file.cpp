#include "../include/file.h"
#include "../include/content.h"
#include <SFML/Graphics.hpp>

namespace file
{
    std::vector<LoadVariable> loadvariables;
    std::vector<ID> definition;
}
template<typename T>
int getContentID(std::vector<T> &contentlist, const std::string &contentname)
{
    if(contentname=="")
    {
        contentlist.push_back(T());
        return contentlist.size()-1;
    }
    for(int i=0;i<content::ids.size();i++)
    {
        if(content::ids[i].text==contentname)
        {
            std::cout<<contentname<<" is now redefined.\n";
            return content::ids[i].num;
        }
    }
    content::ids.push_back(ID(contentlist.size(),contentname));
    contentlist.push_back(T());
    return contentlist.size()-1;
}
template<typename T>
T &getContent(std::vector<T> &contentlist, const std::string &contentname)
{
    return contentlist[getContentID<T>(contentlist,contentname)];
}

sf::Texture* _createTexture(std::ifstream &file,std::string contentname,std::string &LINE)
{
    if(LINE!="(")
    {
        content::textures.push_back(sf::Texture());
        content::textures.back().loadFromFile("content/"+contentname+"/texture/"+LINE+".png");
        return &content::textures.back();
    }

    sf::RenderTexture RENDERTEX;
    bool created=false;
    sf::Color color;
    sf::Texture texture;
    int dimensionX=1,dimensionY=1;
    int posX=0,posY=0;

    while(getWord(file,LINE," \n\t","()[]"))
    {
        if(LINE==")")
        {
            content::textures.push_back(RENDERTEX.getTexture());
            return &content::textures.back();
        }
        else if(LINE=="(")
        {
            while(getWord(file,LINE," \n\t","()[]"))
            {
                if(LINE==")")
                {
                    break;
                }
                else if(LINE=="color")
                {
                    getWord(file,LINE," \n\t","()[]");
                    color.r=treatValue(LINE);
                    getWord(file,LINE," \n\t","()[]");
                    color.g=treatValue(LINE);
                    getWord(file,LINE," \n\t","()[]");
                    color.b=treatValue(LINE);
                    getWord(file,LINE," \n\t","()[]");
                    color.a=treatValue(LINE);
                }
                else if(LINE=="position")
                {
                    getWord(file,LINE," \n\t","()[]");
                    posX=treatValue(LINE);
                    getWord(file,LINE," \n\t","()[]");
                    posY=treatValue(LINE);
                }
                else if(LINE=="setTexDimension")
                {
                    dimensionX=texture.getSize().x;
                    dimensionY=texture.getSize().y;
                }
                else if(LINE=="dimension")
                {
                    getWord(file,LINE," \n\t","()[]");
                    dimensionX=treatValue(LINE);
                    getWord(file,LINE," \n\t","()[]");
                    dimensionY=treatValue(LINE);
                }
                else if(LINE=="texture")
                {
                    getWord(file,LINE," \n\t","()[]");
                    texture.loadFromFile("content/"+contentname+"/texture/"+LINE+".png");
                }
            }
        }
        else if(LINE=="draw")
        {
            if(!created)
            {
                RENDERTEX.create(dimensionX,dimensionY);
                RENDERTEX.clear(sf::Color::Transparent);
                drawTex(RENDERTEX,texture,0,0,dimensionX,dimensionY,color.r,color.g,color.b,color.a);
                created=true;
            }
            else
            {
                drawTex(RENDERTEX,texture,posX,posY,dimensionX,dimensionY,color.r,color.g,color.b,color.a);
            }
            RENDERTEX.display();
        }
        else if(LINE=="create")
        {
            RENDERTEX.create(dimensionX,dimensionY);
            RENDERTEX.clear(color);
            created=true;
        }
    }

    content::textures.push_back(RENDERTEX.getTexture());
    return &content::textures.back();
}
sf::Texture* createTexture(std::ifstream &file,std::string contentname)
{
    std::string LINE;
    getWord(file,LINE," \n\t","()[]");
    return _createTexture(file,contentname,LINE);
}
std::vector<sf::Texture*> createTextures(std::ifstream &file,std::string contentname)
{
    std::string LINE;
    std::vector<sf::Texture*> ret;
    while(getWord(file,LINE," \n\t","()[]"))
    {
        if(LINE=="]")return ret;
        else ret.push_back(_createTexture(file,contentname,LINE));
    }
}
std::vector<int> createValues(std::ifstream &file,std::string contentname)
{
    std::string LINE;
    std::vector<int> ret;
    while(getWord(file,LINE," \n\t","()[]"))
    {
        if(LINE=="]")return ret;
        else
        {
            std::vector<int> newvec=vecTreatValue(LINE);
            for(int i=0; i<newvec.size(); i++)
                ret.push_back(newvec[i]);
        }
    }
}
bool addLoadVariable(std::string TAG,std::string VALUE)
{
    for(int i=0;i<file::loadvariables.size();i++)
    {
        if(file::loadvariables[i].tag==TAG)
        {
            std::cout<<"Load variable "<<TAG<<" value of "<<file::loadvariables[i].value<<" replaced by "<<VALUE<<".\n";
            file::loadvariables[i].value=VALUE;
            return false;
        }
    }
    LoadVariable newLoadVariable;
    newLoadVariable.tag=TAG;newLoadVariable.value=VALUE;
    file::loadvariables.push_back(newLoadVariable);
    return true;
}
sf::Keyboard::Key stringToKey(std::string STR)
{
    if(STR=="A")return sf::Keyboard::A;
    else if(STR=="B")return sf::Keyboard::B;
    else if(STR=="C")return sf::Keyboard::C;
    else if(STR=="D")return sf::Keyboard::D;
    else if(STR=="E")return sf::Keyboard::E;
    else if(STR=="F")return sf::Keyboard::F;
    else if(STR=="G")return sf::Keyboard::G;
    else if(STR=="H")return sf::Keyboard::H;
    else if(STR=="I")return sf::Keyboard::I;
    else if(STR=="J")return sf::Keyboard::J;
    else if(STR=="K")return sf::Keyboard::K;
    else if(STR=="L")return sf::Keyboard::L;
    else if(STR=="M")return sf::Keyboard::M;
    else if(STR=="N")return sf::Keyboard::N;
    else if(STR=="O")return sf::Keyboard::O;
    else if(STR=="P")return sf::Keyboard::P;
    else if(STR=="Q")return sf::Keyboard::Q;
    else if(STR=="R")return sf::Keyboard::R;
    else if(STR=="S")return sf::Keyboard::S;
    else if(STR=="T")return sf::Keyboard::T;
    else if(STR=="U")return sf::Keyboard::U;
    else if(STR=="V")return sf::Keyboard::V;
    else if(STR=="W")return sf::Keyboard::W;
    else if(STR=="W")return sf::Keyboard::X;
    else if(STR=="Y")return sf::Keyboard::Y;
    else if(STR=="Z")return sf::Keyboard::Z;
    else if(STR=="UP")return sf::Keyboard::Up;
    else if(STR=="DOWN")return sf::Keyboard::Down;
    else if(STR=="RIGHT")return sf::Keyboard::Right;
    else if(STR=="LEFT")return sf::Keyboard::Left;
    else if(STR=="NUM0")return sf::Keyboard::Num0;
    else if(STR=="NUM1")return sf::Keyboard::Num1;
    else if(STR=="NUM2")return sf::Keyboard::Num2;
    else if(STR=="NUM3")return sf::Keyboard::Num3;
    else if(STR=="NUM4")return sf::Keyboard::Num4;
    else if(STR=="NUM5")return sf::Keyboard::Num5;
    else if(STR=="NUM6")return sf::Keyboard::Num6;
    else if(STR=="NUM7")return sf::Keyboard::Num7;
    else if(STR=="NUM8")return sf::Keyboard::Num8;
    else if(STR=="NUM9")return sf::Keyboard::Num9;
    else if(STR=="NUMPAD0")return sf::Keyboard::Numpad0;
    else if(STR=="NUMPAD1")return sf::Keyboard::Numpad1;
    else if(STR=="NUMPAD2")return sf::Keyboard::Numpad2;
    else if(STR=="NUMPAD3")return sf::Keyboard::Numpad3;
    else if(STR=="NUMPAD4")return sf::Keyboard::Numpad4;
    else if(STR=="NUMPAD5")return sf::Keyboard::Numpad5;
    else if(STR=="NUMPAD6")return sf::Keyboard::Numpad6;
    else if(STR=="NUMPAD7")return sf::Keyboard::Numpad7;
    else if(STR=="NUMPAD8")return sf::Keyboard::Numpad8;
    else if(STR=="NUMPAD9")return sf::Keyboard::Numpad9;
    else if(STR=="SPACE")return sf::Keyboard::Space;
    else if(STR=="TAB")return sf::Keyboard::Tab;
    else if(STR=="-")return sf::Keyboard::Subtract;
    else if(STR=="*")return sf::Keyboard::Multiply;
    else if(STR=="=")return sf::Keyboard::Equal;
    else if(STR=="+")return sf::Keyboard::Add;
}
bool getWord(std::ifstream &file,std::string &WORD,std::string SEPARATOR,std::string WORDCHAR,std::string EXCLUSIONSTART,std::string EXCLUSIONEND)
{
    std::string word="";
    char CHAR;
    while(file.get(CHAR))
    {
        bool addChar=true;
        if(CHAR=='#')
        {
            std::string TAG="";
            while(file.get(CHAR))
            {
                if(CHAR=='#')
                {
                    bool BREAK=false;
                    for(int i=0;i<file::loadvariables.size();i++)
                    {
                        if(TAG==file::loadvariables[i].tag)
                        {
                            word+=file::loadvariables[i].value;
                            BREAK=true;
                            break;
                        }
                    }
                    if(BREAK)break;
                    std::cout<<"ERROR:The load variable "<<TAG<<" is not defined.\n";
                    word+=TAG;
                    break;
                }
                else
                {
                    TAG+=CHAR;
                }
            }
            file.get(CHAR);
        }
        if(CHAR=='"')
        {
            while(file.get(CHAR))
            {
                if(CHAR=='"')break;
                else word+=CHAR;
            }
            addChar=false;
        }
        for(int i=0;i<SEPARATOR.size();i++)
        {
            if(SEPARATOR[i]==CHAR)
            {
                if(word.size()>0)
                {
                    WORD=word;
                    return true;
                }
                else
                {
                    addChar=false;
                    break;
                }
            }
        }
        for(int i=0;i<WORDCHAR.size();i++)
        {
            if(WORDCHAR[i]==CHAR)
            {
                if(word.size()>0)
                {
                    file.unget();
                    WORD=word;
                    return true;
                }
                else
                {
                    word+=CHAR;
                    WORD=word;
                    return true;
                }
            }
        }
        if(addChar)
        {
            if(CHAR=='\\')
            {
                file.get(CHAR);
                if(CHAR=='\\')word+='\\';
                else if(CHAR=='n')word+='\n';
                else if(CHAR=='_')word+=' ';
                else word+=CHAR;
            }
            else word+=CHAR;
        }
        for(int i=0;i<EXCLUSIONSTART.size();i++)
        {
            if(CHAR==EXCLUSIONSTART[i])
            {
                int boxNumber=0;
                while(file.get(CHAR))
                {
                    bool BREAK=false;
                    for(int i=0;i<EXCLUSIONEND.size();i++)
                    {
                        if(CHAR==EXCLUSIONEND[i])
                        {
                            if(boxNumber==0)
                            {
                                BREAK=true;
                                break;
                            }
                            else
                            {
                                boxNumber--;
                            }
                        }
                    }
                    for(int i=0;i<EXCLUSIONSTART.size();i++)
                    {
                        if(CHAR==EXCLUSIONSTART[i])
                        {
                            boxNumber++;
                        }
                    }
                    word+=CHAR;
                    if(BREAK)break;
                }
            }
        }
    }
    if(word.size()>0)
    {
        WORD=word;
        return true;
    }
    else
    {
        return false;
    }
}
ComplexZone createZone(std::ifstream &file)
{
    std::string LINE;
    ComplexZone newComplexZone;
    while(getWord(file,LINE," \n\t","}])"))
    {
        if(LINE==")")return newComplexZone;
        else
        {
            SquareZone newSquareZone;
            newSquareZone.b1.x=treatValue(LINE);
            getWord(file,LINE," \n\t","}])");
            newSquareZone.b1.y=treatValue(LINE);
            getWord(file,LINE," \n\t","}])");
            newSquareZone.b2.x=treatValue(LINE);
            getWord(file,LINE," \n\t","}])");
            newSquareZone.b2.y=treatValue(LINE);
            newComplexZone.squares.push_back(newSquareZone);
        }
    }

}
intColor createIntColor(std::ifstream &file)
{
    intColor color;

    std::string LINE;
    getWord(file,LINE," \n\t","()[]");
    if(LINE=="rgb:")
    {
        color.r=treatValue(getWordReturn(file," \n\t","()[]"));
        color.g=treatValue(getWordReturn(file," \n\t","()[]"));
        color.b=treatValue(getWordReturn(file," \n\t","()[]"));
        color.a=255;
    }
    else if(LINE=="rgba:")
    {
        color.r=treatValue(getWordReturn(file," \n\t","()[]"));
        color.g=treatValue(getWordReturn(file," \n\t","()[]"));
        color.b=treatValue(getWordReturn(file," \n\t","()[]"));
        color.a=treatValue(getWordReturn(file," \n\t","()[]"));
    }
    else if(LINE=="name:")
    {
        getWord(file,LINE," \n\t","()[]");
        if(LINE=="red"){color.r=255; color.g=0; color.b=0;}
        else if(LINE=="orange"){color.r=255; color.g=150; color.b=0;}
        else if(LINE=="yellow"){color.r=255; color.g=255; color.b=0;}
        else if(LINE=="lime"){color.r=200; color.g=255; color.b=0;}
        else if(LINE=="green"){color.r=0; color.g=255; color.b=0;}
        else if(LINE=="khaki"){color.r=100; color.g=130; color.b=100;}
        else if(LINE=="cyan"){color.r=0; color.g=255; color.b=200;}
        else if(LINE=="skyblue"){color.r=0; color.g=255; color.b=255;}
        else if(LINE=="blue"){color.r=0; color.g=0; color.b=255;}
        else if(LINE=="purple"){color.r=100; color.g=0; color.b=255;}
        else if(LINE=="magenta"){color.r=255; color.g=0; color.b=255;}
        else if(LINE=="pink"){color.r=255; color.g=150; color.b=255;}
        else if(LINE=="black"){color.r=0; color.g=0; color.b=0;}
        else if(LINE=="white"){color.r=255; color.g=255; color.b=255;}
        else if(LINE=="gray"){color.r=150; color.g=150; color.b=150;}
        else if(LINE=="silver"){color.r=200; color.g=200; color.b=200;}
        else if(LINE=="brown"){color.r=130; color.g=100; color.b=0;}

        color.a=treatValue(getWordReturn(file," \n\t","()[]"));
    }

    return color;
}
Color createColor(std::ifstream &file)
{
    intColor ic=createIntColor(file);
    return {ic.r,ic.g,ic.b};
}
sf::Color createSfColor(std::ifstream &file)
{
    intColor ic=createIntColor(file);
    return sf::Color(ic.r,ic.g,ic.b,ic.a);
}
intColor loadIntColor(std::ifstream &file)
{
    std::string LINE;
    intColor color;

    getWord(file,LINE," \n\t","}]");
    color.r=treatValue(LINE);

    getWord(file,LINE," \n\t","}]");
    color.g=treatValue(LINE);

    getWord(file,LINE," \n\t","}]");
    color.b=treatValue(LINE);

    getWord(file,LINE," \n\t","}]");
    color.a=treatValue(LINE);

    return color;
}
bool addID(std::string text,int num,bool isDefinition=false)
{
    for(int i=0;i<content::ids.size();i++)
    {
        if(content::ids[i].text==text)
        {
            if(!isDefinition)std::cout<<"Id "<<text<<" value of "<<content::ids[i].num<<" replaced by "<<num<<".\n";
            content::ids[i].num=num;
            return false;
        }
    }
    ID newID;
    newID.num=num;newID.text=text;
    content::ids.push_back(newID);
    return true;
}
int numFromTextID(std::string text)
{
    for(int i=0;i<content::ids.size();i++)
    {
        if(content::ids[i].text==text)
        {
            return content::ids[i].num;
        }
    }
    std::cout<<"Id "<<text<<" is undefined.\n";
    return 123123;
}
Value compileValueValue(std::string LINE,std::vector<std::string> &variables)
{
    Value newValue;
    if(LINE[0]=='=')
    {
        newValue.value.push_back(numFromTextID(getFrom(LINE,1)));
        newValue.type=ArgumentType::value;
    }
    else
    {
        std::vector<std::string> valueSplited=explode(LINE,"=");
        if(valueSplited[0]=="id")
        {
            newValue.value.push_back(numFromTextID(valueSplited[1]));
            newValue.type=ArgumentType::value;
        }
        else if(valueSplited[0]=="true")
        {
            newValue.value.push_back(1);
            newValue.type=ArgumentType::value;
        }
        else if(valueSplited[0]=="false")
        {
            newValue.value.push_back(0);
            newValue.type=ArgumentType::value;
        }
        else if(valueSplited[0]=="none")
        {
            newValue.value.push_back(-1);
            newValue.type=ArgumentType::value;
        }
        else if(valueSplited[0]=="tag")
        {
            newValue.value.push_back(numFromTextID(valueSplited[1]));
            newValue.type=ArgumentType::tag;
        }
        else if(valueSplited[0]=="var")
        {
            std::string variablename=valueSplited[1];
            int variablenum=-1;

            for(int y=0;y<variables.size();y++)
            {
                if(variablename==variables[y])variablenum=y;
            }
            if(variablenum==-1)
            {
                variablenum=variables.size();
                variables.push_back(valueSplited[1]);
            }

            newValue.value.push_back(variablenum);
            newValue.type=ArgumentType::var;
        }
        else if(valueSplited[0]=="globalvar")
        {
            std::string variablename=valueSplited[1];
            int variablenum=-1;

            for(int y=0;y<content::globalVar.size();y++)
            {
                if(variablename==content::globalVar[y].text)variablenum=y;
            }
            if(variablenum==-1)
            {
                variablenum=content::globalVar.size();
                GlobalVariable newVar;
                newVar.text=variablename;
                content::globalVar.push_back(newVar);
            }

            newValue.value.push_back(variablenum);
            newValue.type=ArgumentType::globalvar;
        }
        else if(valueSplited[0]=="objectvar")
        {
            newValue.value=vecTreatValue2(valueSplited[1],variables);
            newValue.type=ArgumentType::objectvar;
        }
        else if(valueSplited[0]=="state")
        {
            newValue.value.push_back(0);
            newValue.type=ArgumentType::dynamic;
        }
        else if(valueSplited[0]=="states")
        {
            newValue.value.push_back(1);
            newValue.type=ArgumentType::dynamic;
        }
        else if(valueSplited[0]=="type")
        {
            newValue.value.push_back(2);
            newValue.type=ArgumentType::dynamic;
        }
        else if(valueSplited[0]=="types")
        {
            newValue.value.push_back(3);
            newValue.type=ArgumentType::dynamic;
        }
        else if(valueSplited[0]=="cursorx")
        {
            newValue.value.push_back(4);
            newValue.type=ArgumentType::dynamic;
        }
        else if(valueSplited[0]=="cursory")
        {
            newValue.value.push_back(5);
            newValue.type=ArgumentType::dynamic;
        }
        else if(valueSplited[0]=="timer")
        {
            newValue.value.push_back(6);
            newValue.type=ArgumentType::dynamic;
        }
        else if(valueSplited[0]=="commandgroup")
        {
            newValue.value.push_back(7);
            newValue.type=ArgumentType::dynamic;
        }
        else if(valueSplited[0]=="worldsizex")
        {
            newValue.value.push_back(8);
            newValue.type=ArgumentType::dynamic;
        }
        else if(valueSplited[0]=="worldsizey")
        {
            newValue.value.push_back(9);
            newValue.type=ArgumentType::dynamic;
        }
        else if(valueSplited[0]=="windowwidth")
        {
            newValue.value.push_back(10);
            newValue.type=ArgumentType::dynamic;
        }
        else if(valueSplited[0]=="windowheight")
        {
            newValue.value.push_back(11);
            newValue.type=ArgumentType::dynamic;
        }
        else if(valueSplited[0]=="isOutside")
        {
            newValue.value.push_back(13);
            newValue.type=ArgumentType::dynamic;
        }
        else if(valueSplited[0]=="didAssociate")
        {
            newValue.value.push_back(12);
            newValue.type=ArgumentType::dynamic;
        }
        else
        {
            newValue.value=vecTreatValue3(LINE,variables);
            newValue.type=ArgumentType::value;
        }
    }
    return newValue;
}
std::vector<Modifier> createModifier(std::string modifierline,std::vector<std::string> &variables);
Argument treatAIValue(std::string LINE,std::vector<std::string> &variables)
{
    Argument RETURN;
    std::vector<std::string> splited=explode(LINE,"","+-*/[]&|","<",">");
    for(int i=0;i<splited.size();i+=2)
    {
        if(splited[i]=="[")
        {
            Value newValue;
            newValue.operat=ArgOperator::elementstart;
            RETURN.values.push_back(newValue);
            i++;
        }
        else if(splited[i]=="]")
        {
            Value newValue;
            newValue.operat=ArgOperator::elementend;
            RETURN.values.push_back(newValue);
            i++;
        }
        if(i>=splited.size())break;

        ArgOperator valueOperator;
        if(splited[i]=="+")valueOperator=ArgOperator::plus;
        else if(splited[i]=="-")valueOperator=ArgOperator::minus;
        else if(splited[i]=="*")valueOperator=ArgOperator::multiply;
        else if(splited[i]=="/")valueOperator=ArgOperator::divide;
        else if(splited[i]=="/")valueOperator=ArgOperator::divide;
        else if(splited[i]=="&")valueOperator=ArgOperator::et;
        else if(splited[i]=="|")valueOperator=ArgOperator::ou;
        else
        {
            valueOperator=ArgOperator::plus;+
            i--;
        }

        if(valueOperator==ArgOperator::plus&&splited[i+1]=="+")
        {
            i++;
            valueOperator=ArgOperator::pushback;
        }

        Value newValue;
        std::string modifierline=getFromChar(splited[i+1],'(',')');
        newValue.modifiers=createModifier(modifierline,variables);
        std::string valueline=getFrom(splited[i+1],modifierline.size()+2*(splited[i+1][0]=='('),-1);

        newValue=compileValueValue(valueline,variables);

        newValue.operat=valueOperator;

        RETURN.values.push_back(newValue);
    }
    return RETURN;
}
Argument treatAIValue(std::string LINE)
{
    std::vector<std::string> variables;
    return treatAIValue(LINE,variables);
}
void createKeyConfig(std::ifstream &file,std::string contentname)
{
    std::string LINE;
    KeyConfig newKeyConfig;

    while(getWord(file,LINE," \n\t","}]"))
    {
        if(LINE=="CURSORUP:")
        {
            getWord(file,LINE," \n\t","}]");
            newKeyConfig.up=stringToKey(LINE);
        }
        else if(LINE=="CURSORDOWN:")
        {
            getWord(file,LINE," \n\t","}]");
            newKeyConfig.down=stringToKey(LINE);
        }
        else if(LINE=="CURSORLEFT:")
        {
            getWord(file,LINE," \n\t","}]");
            newKeyConfig.left=stringToKey(LINE);
        }
        else if(LINE=="CURSORRIGHT:")
        {
            getWord(file,LINE," \n\t","}]");
            newKeyConfig.right=stringToKey(LINE);
        }
        else if(LINE=="CATEGORYNEXT:")
        {
            getWord(file,LINE," \n\t","}]");
            newKeyConfig.categoryNext=stringToKey(LINE);
        }
        else if(LINE=="CATEGORYPREVIOUS:")
        {
            getWord(file,LINE," \n\t","}]");
            newKeyConfig.categoryPrevious=stringToKey(LINE);
        }
        else if(LINE=="NEXT:")
        {
            getWord(file,LINE," \n\t","}]");
            newKeyConfig.spawnNext=stringToKey(LINE);
        }
        else if(LINE=="PREVIOUS:")
        {
            getWord(file,LINE," \n\t","}]");
            newKeyConfig.spawnPrevious=stringToKey(LINE);
        }
        else if(LINE=="CUSTOMKEYS[")
        {
            while(getWord(file,LINE," \n\t","}]"))
            {
                if(LINE=="]")break;
                else
                {
                    newKeyConfig.customKeys.push_back(stringToKey(LINE));
                }
            }
        }
        else if(LINE=="CREATE:")
        {
            getWord(file,LINE," \n\t","}]");
            newKeyConfig.createObject=stringToKey(LINE);
        }
        else if(LINE=="}")
        {
            content::keyConfig.push_back(newKeyConfig);
            return;
        }
    }
}
int treatValue(std::string LINE)
{
    std::vector<std::string> variables;
    Argument argument;argument=treatAIValue(LINE,variables);
    ScriptTarget target;
    return treatArg(argument,target,global::terrain);
}
std::vector<int> vecTreatValue(std::string LINE)
{
    std::vector<std::string> variables;
    Argument argument;argument=treatAIValue(LINE,variables);
    ScriptTarget target;
    return vecTreatArg(argument,target,global::terrain);
}
std::vector<int> vecTreatValue2(std::string LINE,std::vector<std::string> &variables)
{
    if(LINE[0]=='<')return vecTreatValue(getFrom(LINE,1,-2));
    else
    {
        std::vector<int> returns;returns.push_back(compileValueValue(LINE,variables).value[0]);
        return returns;
    }
}
std::vector<int> vecTreatValue3(std::string LINE,std::vector<std::string> &variables)
{
    if(LINE[0]=='<')return vecTreatValue(getFrom(LINE,1,-2));
    else
    {
        std::vector<int> returns;returns.push_back(StringToInt(LINE));
        return returns;
    }
}
std::string getWordReturn(std::ifstream &file,std::string SEPARATOR,std::string WORDCHAR,std::string EXCLUSIONSTART,std::string EXCLUSIONEND)
{
    std::string LINE;
    getWord(file,LINE,SEPARATOR,WORDCHAR,EXCLUSIONSTART,EXCLUSIONEND);
    return LINE;
}
std::vector<Modifier> createModifier(std::string modifierline,std::vector<std::string> &variables)
{
    std::vector<Modifier> RETURN;
    std::vector<std::string> parts=explode(modifierline," \t\n");
    for(int i=0;i<parts.size();i++)
    {
        if(parts[i]=="offset")
        {
            Modifier newModifier;
            newModifier.type=ModifierType::offset1;
            newModifier.arguments.push_back(treatAIValue(parts[i+1],variables));
            newModifier.arguments.push_back(treatAIValue(parts[i+2],variables));
            RETURN.push_back(newModifier);
            i+=2;
        }
        else if(parts[i]=="at")
        {
            Modifier newModifier;
            newModifier.type=ModifierType::pos1;
            newModifier.arguments.push_back(treatAIValue(parts[i+1],variables));
            newModifier.arguments.push_back(treatAIValue(parts[i+2],variables));
            RETURN.push_back(newModifier);
            i+=2;
        }
        else if(parts[i]=="num")
        {
            Modifier newModifier;
            newModifier.type=ModifierType::num1;
            newModifier.arguments.push_back(treatAIValue(parts[i+1],variables));
            RETURN.push_back(newModifier);
            i+=1;
        }
        else if(parts[i]=="team")
        {
            Modifier newModifier;
            newModifier.type=ModifierType::team1;
            newModifier.arguments.push_back(treatAIValue(parts[i+1],variables));
            RETURN.push_back(newModifier);
            i+=1;
        }
    }
    return RETURN;
}
CommandGroup createCGroup(std::ifstream &file,std::string contentname,std::vector<std::string> &variables)
{
    std::string LINE;
    std::vector<Modifier> modifiers;
    std::vector<int> endIfPlace;

    CommandGroup newCommandGroup;

    while(getWord(file,LINE," \n\t","(){}"))
    {
        if(LINE=="}")
        {
            return newCommandGroup;
        }
        else if(LINE[0]=='-')
        {
            Command newCommand;
            if(LINE=="-move")
            {
                newCommand.modifiers=modifiers;
                newCommand.command=command::move;
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommandGroup.commands.push_back(newCommand);
            }
            else if(LINE=="-call")
            {
                newCommand.modifiers=modifiers;
                newCommand.command=command::usefunction;
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommandGroup.commands.push_back(newCommand);
            }
            else if(LINE=="-include")
            {
                std::vector<int> ids=vecTreatValue(getWordReturn(file," \n\t","{}","(",")"));
                for(int y=0; y<ids.size(); y++)
                {
                    CommandGroup &func=content::functions[ids[y]];
                    for(int i=0; i<func.commands.size(); i++)
                        newCommandGroup.commands.push_back(func.commands[i]);
                }
            }
            else if(LINE=="-setObjectTex")
            {
                newCommand.modifiers=modifiers;
                newCommand.command=command::setObjectTex;
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommandGroup.commands.push_back(newCommand);
            }
            else if(LINE=="-setStateTex")
            {
                newCommand.modifiers=modifiers;
                newCommand.command=command::setStateTex;
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommandGroup.commands.push_back(newCommand);
            }
            else if(LINE=="-break")
            {
                newCommand.command=command::breek;
                newCommandGroup.commands.push_back(newCommand);
            }
            else if(LINE=="-setState")
            {
                newCommand.modifiers=modifiers;
                newCommand.command=command::setState;
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommandGroup.commands.push_back(newCommand);
            }
            else if(LINE=="-setglobal")
            {
                std::string variablename=getWordReturn(file," \n\t","{}","(",")");
                Argument variablevalue=treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables);
                int variablenum=-1;

                for(int y=0;y<content::globalVar.size();y++)
                    if(variablename==content::globalVar[y].text)variablenum=y;

                if(variablenum==-1)
                {
                    GlobalVariable newGlobalVar;
                    newGlobalVar.text=variablename;
                    newGlobalVar.value=variablevalue;
                    content::globalVar.push_back(newGlobalVar);
                    variablenum=content::globalVar.size()-1;
                }

                Value newValue;newValue.value.push_back(variablenum);newValue.type=ArgumentType::globalvarnum;
                Argument argnum;argnum.values.push_back(newValue);

                newCommand.modifiers=modifiers;
                newCommand.command=command::globalvarset;
                newCommand.argument.push_back(argnum);
                newCommand.argument.push_back(variablevalue);
                newCommandGroup.commands.push_back(newCommand);
            }
            else if(LINE=="-setObject")
            {
                newCommand.command=command::setObject;
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommandGroup.commands.push_back(newCommand);
            }
            else if(LINE=="-setMenu")
            {
                Command newCommand;
                newCommand.command=command::setmenu;
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommandGroup.commands.push_back(newCommand);
            }
            else if(LINE=="-setTimer")
            {
                newCommand.command=command::settimer;
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommandGroup.commands.push_back(newCommand);
            }
            else if(LINE=="-setCommandGroup")
            {
                newCommand.command=command::setcgroup;
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommandGroup.commands.push_back(newCommand);
            }
            else if(LINE=="-ifObject")
            {
                newCommand.modifiers=modifiers;
                newCommand.command=command::ifObject;
                newCommand.argument.push_back(compOperatorToArgument(getWordReturn(file," \n\t","{}","(",")")));
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommandGroup.commands.push_back(newCommand);

                endIfPlace.push_back(newCommandGroup.commands.size()-1);
            }
            else if(LINE=="-if")
            {
                newCommand.modifiers=modifiers;
                newCommand.command=command::ifall;
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommand.argument.push_back(compOperatorToArgument(getWordReturn(file," \n\t","{}","(",")")));
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommandGroup.commands.push_back(newCommand);

                endIfPlace.push_back(newCommandGroup.commands.size()-1);
            }
            else if(LINE=="-ifState")
            {
                newCommand.modifiers=modifiers;
                newCommand.command=command::ifState;
                newCommand.argument.push_back(compOperatorToArgument(getWordReturn(file," \n\t","{}","(",")")));
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommandGroup.commands.push_back(newCommand);

                endIfPlace.push_back(newCommandGroup.commands.size()-1);
            }
            else if(LINE=="-ifSomeoneKeyPressed")
            {
                newCommand.modifiers=modifiers;
                newCommand.command=command::ifSomeoneKeyPressed;
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommandGroup.commands.push_back(newCommand);

                endIfPlace.push_back(newCommandGroup.commands.size()-1);
            }
            else if(LINE=="-ifKeyPressed")
            {
                newCommand.modifiers=modifiers;
                newCommand.command=command::ifKeyPressed;
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommandGroup.commands.push_back(newCommand);

                endIfPlace.push_back(newCommandGroup.commands.size()-1);
            }
            else if(LINE=="-ifOneObject")
            {
                newCommand.modifiers=modifiers;
                newCommand.command=command::ifOneObject;
                newCommand.argument.push_back(compOperatorToArgument(getWordReturn(file," \n\t","{}","(",")")));
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommandGroup.commands.push_back(newCommand);

                endIfPlace.push_back(newCommandGroup.commands.size()-1);
            }
            else if(LINE=="-ifOneState")
            {
                newCommand.modifiers=modifiers;
                newCommand.command=command::ifOneState;
                newCommand.argument.push_back(compOperatorToArgument(getWordReturn(file," \n\t","{}","(",")")));
                newCommand.argument.push_back(treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables));
                newCommandGroup.commands.push_back(newCommand);

                endIfPlace.push_back(newCommandGroup.commands.size()-1);
            }
            else if(LINE=="-ifOneOutside")
            {
                newCommand.modifiers=modifiers;
                newCommand.command=command::ifOneOutside;
                newCommandGroup.commands.push_back(newCommand);

                endIfPlace.push_back(newCommandGroup.commands.size()-1);
            }
            else if(LINE=="-ifOneInside")
            {
                newCommand.modifiers=modifiers;
                newCommand.command=command::ifOneInside;
                newCommandGroup.commands.push_back(newCommand);

                endIfPlace.push_back(newCommandGroup.commands.size()-1);
            }
            else if(LINE=="-set")
            {
                std::string variablename=getWordReturn(file," \n\t","{}","(",")");
                Argument variablevalue=treatAIValue(getWordReturn(file," \n\t","{}","(",")"),variables);
                int variablenum=-1;

                for(int y=0;y<variables.size();y++)
                {
                    if(variablename==variables[y])variablenum=y;
                }
                if(variablenum==-1)
                {
                    variables.push_back(variablename);
                    variablenum=variables.size()-1;
                }
                Value newValue;newValue.value.push_back(variablenum);newValue.type=ArgumentType::varnum;
                Argument argnum;argnum.values.push_back(newValue);

                newCommand.modifiers=modifiers;
                newCommand.command=command::variableset;
                newCommand.argument.push_back(argnum);
                newCommand.argument.push_back(variablevalue);
                newCommandGroup.commands.push_back(newCommand);
            }
            else if(LINE=="-endIf")
            {
                Value newValue;newValue.value.push_back(newCommandGroup.commands.size()-endIfPlace[endIfPlace.size()-1]);
                newValue.type=ArgumentType::value;
                newValue.operat=ArgOperator::plus;
                Argument newArgument;newArgument.values.push_back(newValue);

                newCommandGroup.commands[endIfPlace[endIfPlace.size()-1]].argument.push_back(newArgument);
                endIfPlace.erase(endIfPlace.end()-1);
            }
            modifiers.clear();
        }
        else if(LINE=="(")
        {
            std::string modifierline;
            while(getWord(file,LINE," \n\t","{}"))
            {
                if(LINE==")")
                {
                    modifierline=getFrom(modifierline,0,-2);
                    modifiers=createModifier(modifierline,variables);
                    break;
                }
                else
                {
                    modifierline+=LINE+" ";
                }
            }

        }
    }
}
void createFunction(std::ifstream &file,std::string contentname)
{
    std::vector<std::string> variables;
    CommandGroup cgroup=createCGroup(file,contentname,variables);
    std::string name;
    getWord(file,name," \n\t","{}()");

    getContent<CommandGroup>(content::functions,name)=cgroup;
}
void createScript2(std::ifstream &file,std::string contentname)
{
    std::string LINE;
    std::string name;

    Script newScript;

    std::vector<std::string> variables;

    while(getWord(file,LINE," \n\t","{}()"))
    {
        if(LINE=="{")
        {
            getWord(file,LINE," \n\t","{}()");
            int duration=treatValue(LINE);
            newScript.commandGroup.push_back(createCGroup(file,contentname,variables));
            newScript.commandGroup.back().duration=duration;
        }
        else if(LINE=="INCLUDE")
        {
            std::vector<int> ids=vecTreatValue(getWordReturn(file," \n\t","{}()"));
            int duration=treatValue(getWordReturn(file," \n\t","{}()"));

            for(int y=0; y<ids.size(); y++)
            {
                newScript.commandGroup.push_back(content::functions[ids[y]]);
                newScript.commandGroup.back().duration=duration;
            }
        }
        else if(LINE=="NAME:")
        {
            getWord(file,LINE," \n\t","{}()");
            name=LINE;
        }
        else if(LINE=="}")
        {
            getContent<Script>(content::scripts,name)=newScript;
            return;
        }
    }
}
void createObjectType(std::ifstream &file,std::string contentname)
{
    ObjectType newType;

    std::string LINE;
    std::string name;
    while(getWord(file,LINE," \n\t","}]"))
    {
        if(LINE=="TEXTURE[")
        {
            newType.textures=createTextures(file,contentname);
        }
        else if(LINE=="VARIABLES[")
        {
            while(getWord(file,LINE," \n\t","}]","(",")"))
            {
                if(LINE=="]")break;
                else
                {
                    newType.variables.push_back(treatValue( LINE ));
                }
            }
        }
        else if(LINE=="NAME:")
        {
            getWord(file,LINE," \n\t","}]");
            name=LINE;
        }
        else if(LINE=="}")
        {
            getContent<ObjectType>(content::objectType,name)=newType;
            return;
        }
    }
}
void createArena(std::ifstream &file,std::string contentname)
{
    ScriptTarget target;
    Arena newArena=Arena();
    ArenaObject newAObject=ArenaObject();

    std::string LINE;
    std::string name;

    while(getWord(file,LINE," \n\t",""))
    {
        if(LINE=="----")
        {
            newArena.objects.push_back(newAObject);
            newAObject=ArenaObject();
        }
        else if(LINE=="POSITION:")
        {
            newAObject.X1=treatAIValue(getWordReturn(file," \n\t","}]"));
            newAObject.Y1=treatAIValue(getWordReturn(file," \n\t","}]"));
            newAObject.X2=treatAIValue(getWordReturn(file," \n\t","}]"));
            newAObject.Y2=treatAIValue(getWordReturn(file," \n\t","}]"));
        }
        else if(LINE=="SPAWNCHANCE:")
        {
            newAObject.chanceToSpawn=treatAIValue(getWordReturn(file," \n\t","}]"));
        }
        else if(LINE=="POSITIONOFFSET:")
        {
            newAObject.posRandOffset=treatAIValue(getWordReturn(file," \n\t","}]"));
        }
        else if(LINE=="CLEAR:")
        {
            newAObject.doClear=treatValue(getWordReturn(file," \n\t","}]"));
        }
        else if(LINE=="SYNC:")
        {
            newAObject.typeStateSync=treatValue(getWordReturn(file," \n\t","}]"));
        }
        else if(LINE=="STATES[")
        {
            while(getWord(file,LINE," \n\t",""))
            {
                if(LINE=="]"){break;}
                else
                {
                    newAObject.ObjectStates.push_back(treatAIValue(LINE));
                }
            }
        }
        else if(LINE=="OBJECTS[")
        {
            while(getWord(file,LINE," \n\t",""))
            {
                if(LINE=="]")break;
                else
                {
                    newAObject.objectTypes.push_back(treatAIValue(LINE));
                }
            }
        }
        else if(LINE=="NAME:")
        {
            getWord(file,LINE," \n\t","}]");
            name=LINE;
        }
        else if(LINE=="}")
        {
            newArena.objects.push_back(newAObject);
            getContent<Arena>(content::arenas,name)=newArena;
            return;
        }
    }
}
void createTag(std::ifstream &file,std::string contentname)
{
    Tag newTag;

    std::string LINE,name;
    while(getWord(file,LINE," \n\t",""))
    {

        if(LINE=="NAME:")
        {
            getWord(file,LINE," \n\t","}");
            name=LINE;
        }
        else if(LINE=="IDS[")
        {
            while(getWord(file,LINE," \n\t",""))
            {
                if(LINE=="]")break;
                else
                {
                    newTag.nums.push_back(treatValue(LINE));
                }
            }
        }
        else if(LINE=="}")
        {
            getContent<Tag>(content::tags,name)=newTag;
            return;
        }
    }
}
void createID(std::ifstream &file,std::string contentname)
{
    Tag newTag;
    int existingTag=-1;

    std::string LINE;
    while(getWord(file,LINE," \n\t","]"))
    {
            if(LINE=="]")return;
            else
            {
                ID newID;

                newID.text=treatValue(LINE);
                getWord(file,LINE," \n\t","]");
                newID.num=treatValue(LINE);

                content::ids.push_back(newID);
            }
    }
}
void playerInput(std::ifstream &file,std::string contentname)
{
    std::string question;
    std::vector<std::string> inputreponse;
    std::vector<std::string> outputreponse;
    std::string variabletag;
    std::string LINE;
    while(getWord(file,LINE," \n\t","}]"))
    {
        if(LINE=="]")
        {
            std::cout<<question<<"\n";
            std::string input;
            std::getline(std::cin,input);
            for(int i=0;i<inputreponse.size();i++)
            {
                if(input==inputreponse[i])
                {
                    addLoadVariable(variabletag,outputreponse[i]);
                    return;
                }
            }
            addLoadVariable(variabletag,input);

            return;
        }
        else if(LINE=="RESPONSE:")
        {
            inputreponse.push_back(LINE);
            getWord(file,LINE," \n\t","}]");
            outputreponse.push_back(LINE);
        }
        else if(LINE=="VARIABLE:")
        {
            getWord(file,LINE," \n\t","}]");
            variabletag=LINE;
        }
        else if(LINE=="TEXT:")
        {
            getWord(file,LINE," \n\t","}]");
            question=LINE;
        }
    }
}
void createSpawnerHand(std::ifstream &file,std::string contentname)
{
    std::string LINE;
    std::string name;
    SpawnerHand newSpawnerHand;
    std::vector<Spawner> newSpawnerCategory;
    Spawner newSpawner;

    newSpawnerHand.colorsOffset.push_back(createIntColor(file));

    while(getWord(file,LINE," \n\t","}]"))
    {
        if(LINE=="----")
        {
            newSpawnerCategory.push_back(newSpawner);

            newSpawnerHand.colorsOffset.push_back(createIntColor(file));
            newSpawnerHand.spawner.push_back(newSpawnerCategory);
            newSpawnerCategory.clear();
        }
        else if(LINE=="--")
        {
            newSpawnerCategory.push_back(newSpawner);
        }
        else if(LINE=="ZONE(")
        {
            newSpawner.zone=createZone(file);
        }
        else if(LINE=="STATE:")
        {
            getWord(file,LINE," \n\t","}]");
            newSpawner.state=treatValue(LINE);
        }
        else if(LINE=="TIMER:")
        {
            getWord(file,LINE," \n\t","}]");
            newSpawner.timer=treatValue(LINE);
            if(global::maxTimer<treatValue(LINE))global::maxTimer=treatValue(LINE);
        }
        else if(LINE=="NAME:")
        {
            getWord(file,LINE," \n\t","}]");
            name=LINE;
        }
        else if(LINE=="OBJECT:")
        {
            getWord(file,LINE," \n\t","}]");
            newSpawner.object=treatValue(LINE);
        }
        else if(LINE=="}")
        {
            newSpawnerCategory.push_back(newSpawner);
            newSpawnerHand.spawner.push_back(newSpawnerCategory);
            getContent<SpawnerHand>(content::spawnerHand,name)=newSpawnerHand;
            return;
        }
    }
}
void createAssociation(std::ifstream &file,std::string contentname)
{
    Association newAssociation;

    std::string LINE,name;
    while(getWord(file,LINE," \n\t","}]"))
    {
        if(LINE=="[")
        {
            int X1,Y1,X2,Y2;
            std::vector<int> state,type;
            while(getWord(file,LINE," \n\t","}]"))
            {
                if(LINE=="]")
                {
                    for(int x=X1;x<=X2;x++)
                    for(int y=Y1;y<=Y2;y++)
                    {
                        AssociateBlock newBlock;
                        newBlock.posX=x;newBlock.posY=y;
                        newBlock.type=type;newBlock.state=state;
                        newAssociation.blocks.push_back(newBlock);
                    }
                    break;
                }
                else if(LINE=="ZONE:")
                {
                    X1=treatValue(getWordReturn(file," \n\t","}]"));
                    Y1=treatValue(getWordReturn(file," \n\t","}]"));
                    X2=treatValue(getWordReturn(file," \n\t","}]"));
                    Y2=treatValue(getWordReturn(file," \n\t","}]"));
                }
                else if(LINE=="STATE[")
                {
                    state=createValues(file,contentname);
                }
                else if(LINE=="OBJECT[")
                {
                    type=createValues(file,contentname);
                }

            }
        }
        else if(LINE=="NAME:")
        {
            name=getWordReturn(file," \n\t","}]");
        }
        else if(LINE=="STATE[")
        {
            if(LINE=="]")break;
            else
            {
                newAssociation.states.push_back(treatValue(getWordReturn(file," \n\t","}]")));
            }
        }
        else if(LINE=="OBJECT[")
        {
            if(LINE=="]")break;
            else
            {
                newAssociation.type.push_back(treatValue(getWordReturn(file," \n\t","}]")));
            }
        }
        else if(LINE=="}")
        {
            getContent<Association>(content::associations,name)=newAssociation;
            return;
        }
    }
}
void createMenu(std::ifstream &file,std::string contentname)
{
    Menu newMenu;

    std::string LINE,name;
    while(getWord(file,LINE," \n\t","}]"))
    {
        if(LINE=="[")
        {
            MenuObject newMenuObject;
            while(getWord(file,LINE," \n\t","}]"))
            {
                if(LINE=="]")
                {
                    newMenu.objects.push_back(newMenuObject);
                    break;
                }
                else if(LINE=="POSITION:")
                {
                    newMenuObject.X1=treatAIValue(getWordReturn(file," \n\t","}]"));
                    newMenuObject.Y1=treatAIValue(getWordReturn(file," \n\t","}]"));
                }
                else if(LINE=="SIZE:")
                {
                    newMenuObject.X2=treatAIValue(getWordReturn(file," \n\t","}]"));
                    newMenuObject.Y2=treatAIValue(getWordReturn(file," \n\t","}]"));
                }
                else if(LINE=="SCRIPT:")
                {
                    newMenuObject.script=treatValue(getWordReturn(file," \n\t","}]"));
                }
                else if(LINE=="TYPE:")
                {
                    std::string type; getWordReturn(file,type," \n\t","}]");
                    if(type=="picture")newMenuObject.type=MenuObjectType::picture;
                    else if(type=="button")newMenuObject.type=MenuObjectType::button;
                    else std::cout<<"ERROR:Menu Object Type \""<<type<<"\" is incorrect.\n";
                }
                else if(LINE=="TEXTURENUM:")
                {
                    newMenuObject.texNum=treatAIValue(getWordReturn(file," \n\t","}]"));
                }
                else if(LINE=="TEXTURE[")
                {
                    newMenuObject.textures=createTextures(file,contentname);
                }

            }
        }
        else if(LINE=="NAME:")
        {
            name=getWordReturn(file," \n\t","}]");
        }
        else if(LINE=="}")
        {
            getContent<Menu>(content::menus,name)=newMenu;
            return;
        }
    }
}
void createTeam(std::ifstream &file,std::string contentname)
{
    Team newTeam;

    std::string LINE,name;
    while(getWord(file,LINE," \n\t","}]"))
    {
        if(LINE=="COLOR:")
        {
            newTeam.color=createSfColor(file);
        }
        else if(LINE=="NAME:")
        {
            name=getWordReturn(file," \n\t","}]");
        }
        else if(LINE=="CURSOR:")
        {
            newTeam.cursorTex=createTexture(file,contentname);
        }
        else if(LINE=="CURSOR2:")
        {
            newTeam.cursor2Tex=createTexture(file,contentname);
        }
        else if(LINE=="SPAWNER:")
        {
            newTeam.spawnerHand=treatValue(getWordReturn(file," \n\t","}]"));
        }
        else if(LINE=="}")
        {
            newTeam.timer=0;
            newTeam.selectedCategory=0;newTeam.selectedSpawner=0;

            getContent<Team>(content::teams,name)=newTeam;
            return;
        }
    }
}
void createObjectState(std::ifstream &file,std::string contentname)
{
    ObjectState newState;

    std::string LINE;
    std::string name;
    while(getWord(file,LINE," \n\t","}]"))
    {
        if(LINE=="TEXTURE[")
        {
            newState.textures=createTextures(file,contentname);
        }
        else if(LINE=="NAME:")
        {
            getWord(file,LINE," \n\t","}]");
            name=LINE;
        }
        else if(LINE=="ICONTEX:")
        {
            getWord(file,LINE," \n\t","}]");
            newState.texIconNumber=treatValue(LINE);
        }
        else if(LINE=="COLOR:")
        {
            newState.color=createSfColor(file);
        }
        else if(LINE=="SCRIPT:")
        {
            getWord(file,LINE," \n\t","}]");
            newState.script=treatValue(LINE);
        }
        else if(LINE=="}")
        {
            getContent<ObjectState>(content::objectState,name)=newState;
            return;
        }
    }
}
void createTerrainSkin(std::ifstream &file,std::string contentname)
{
    TerrainSkin newSkin;

    std::string LINE,name;
    while(getWord(file,LINE," \t\n","}]"))
    {
        if(LINE=="TEXTURE[")
        {
            newSkin.textures=createTextures(file,contentname);
        }
        else if(LINE=="PANNELS:")
        {
            newSkin.pannel=createTexture(file,contentname);
        }
        else if(LINE=="SELECTOR:")
        {
            newSkin.selector=createTexture(file,contentname);
        }
        else if(LINE=="BACKGROUND:")
        {
            newSkin.background=createTexture(file,contentname);
        }
        else if(LINE=="BAR:")
        {
            newSkin.bar=createTexture(file,contentname);
        }
        else if(LINE=="NAME:")
        {
            getWord(file,LINE," \t\n","}]");
            name=LINE;
        }
        else if(LINE=="}")
        {
            getContent<TerrainSkin>(content::terrainSkin,name)=newSkin;
            return;
        }
    }
}
void loadContentFile(std::string filename,std::string contentname)
{
    std::ifstream main("content/"+contentname+"/"+filename+".txt");
    if(!main)std::cout<<"[ERROR]File \""+filename+"\" in pack \""+contentname+"\" does not exist.\n";
    std::string LINE;
    std::string oldcontent=contentname;

    std::vector<std::string> goto_name;
    std::vector<int> goto_place;

    while(getWord(main,LINE," \t\n","}]"))
    {
        if(LINE=="LOAD[")
        {
            while(getWord(main,LINE," \t\n","}]"))
            {
                if(LINE=="]")break;
                else
                {
                    loadContentFile(LINE,contentname);
                }
            }
        }
        else if(LINE=="INPACK")
        {
            getWord(main,LINE," \t\n","}]");
            contentname=LINE;
        }
        else if(LINE=="INMAIN")
        {
            contentname=oldcontent;
        }
        else if(LINE=="LABEL")
        {
            bool newLabel=true;
            getWord(main,LINE," \t\n","}]");
            for(int i=0;i<goto_name.size();i++)
            if(goto_name[i]==LINE)
            {
                goto_place[i]=main.tellg();
                newLabel=false;
            }
            if(newLabel)
            {
                goto_name.push_back(LINE);
                goto_place.push_back(main.tellg());
            }
        }
        else if(LINE=="GOTO")
        {
            bool goForward=true;
            getWord(main,LINE," \t\n","}]");
            for(int i=0;i<goto_name.size();i++)
            if(goto_name[i]==LINE)
            {
                main.clear();
                main.seekg(goto_place[i]-1,main.beg);
                goForward=false;
                break;
            }
            std::string label=LINE;

            if(goForward){
            while(getWord(main,LINE," \t\n","}]")){
            if(LINE=="LABEL")
            {
                getWord(main,LINE," \t\n","}]");
                if(LINE==label)
                {
                    goto_name.push_back(label);
                    goto_place.push_back(main.tellg());
                    break;
                }
            }}}

        }
        else if(LINE=="SAY")
        {
            getWord(main,LINE," \t\n","}]");
            std::cout<<LINE<<"\n";
        }
        else if(LINE=="OBJECT")//---DECLARATION
        {
            getWord(main,LINE," \t\n","}]");
            getContent<ObjectType>(content::objectType,LINE);
        }
        else if(LINE=="SKIN")
        {
            getWord(main,LINE," \t\n","}]");
            getContent<TerrainSkin>(content::terrainSkin,LINE);
        }
        else if(LINE=="FUNCTION")
        {
            getWord(main,LINE," \t\n","}]");
            getContent<CommandGroup>(content::functions,LINE);
        }
        else if(LINE=="STATE")
        {
            getWord(main,LINE," \t\n","}]");
            getContent<ObjectState>(content::objectState,LINE);
        }
        else if(LINE=="SCRIPT")
        {
            getWord(main,LINE," \t\n","}]");
            getContent<Script>(content::scripts,LINE);
        }
        else if(LINE=="ARENA")
        {
            getWord(main,LINE," \t\n","}]");
            getContent<Arena>(content::arenas,LINE);
        }
        else if(LINE=="ASSOCIATION")
        {
            getWord(main,LINE," \t\n","}]");
            getContent<Association>(content::associations,LINE);
        }
        else if(LINE=="SPAWNERS")
        {
            getWord(main,LINE," \t\n","}]");
            getContent<SpawnerHand>(content::spawnerHand,LINE);
        }
        else if(LINE=="TEAM")
        {
            getWord(main,LINE," \t\n","}]");
            getContent<Team>(content::teams,LINE);
        }
        else if(LINE=="MENU")
        {
            getWord(main,LINE," \t\n","}]");
            getContent<Menu>(content::menus,LINE);
        }
        else if(LINE=="KEYCONFIG")
        {
            getWord(main,LINE," \t\n","}]");
            getContent<KeyConfig>(content::keyConfig,LINE);
        }
        else if(LINE=="TAG")
        {
            getWord(main,LINE," \t\n","}]");
            getContent<Tag>(content::tags,LINE);
        }
        else if(LINE=="OBJECT{")
            createObjectType(main,contentname);//---DEFINITION
        else if(LINE=="SKIN{")
            createTerrainSkin(main,contentname);
        else if(LINE=="STATE{")
            createObjectState(main,contentname);
        else if(LINE=="SCRIPT{")
            createScript2(main,contentname);
        else if(LINE=="SPAWNERS{")
            createSpawnerHand(main,contentname);
        else if(LINE=="ARENA{")
            createArena(main,contentname);
        else if(LINE=="FUNCTION{")
            createFunction(main,contentname);
        else if(LINE=="ASSOCIATION{")
            createAssociation(main,contentname);
        else if(LINE=="TEAM{")
            createTeam(main,contentname);
        else if(LINE=="TAG{")
            createTag(main,contentname);
        else if(LINE=="KEYCONFIG{")
            createKeyConfig(main,contentname);//---
        else if(LINE=="CREATEID[")
            createID(main,contentname);
        else if(LINE=="INPUT[")
            playerInput(main,contentname);
        else if(LINE=="MENU{")
            createMenu(main,contentname);
        else if(LINE=="CREATETERRAIN")
        {
            int sizeX=treatValue(getWordReturn(main," \t\n","}]"));
            int sizeY=treatValue(getWordReturn(main," \t\n","}]"));
            global::terrain.create(sizeX,sizeY);
        }
        else if(LINE=="IF")
        {
            std::string comp1,comp2,comparator;
            comp1=getWordReturn(main," \t\n","}]");
            comparator=getWordReturn(main," \t\n","}]");
            comp2=getWordReturn(main," \t\n","}]");

            bool pass=true;
            if(comparator=="=")
            {
                if(comp1==comp2)pass=false;
            }
            else if(comparator=="!=")
            {
                if(comp1!=comp2)pass=false;
            }
            if(pass)
            {
                while(getWord(main,LINE," \t\n","}]"))
                    if(LINE=="ENDIF")break;
            }
        }
        else if(LINE=="(")
        {
            file::loadvariables.clear();
            while(getWord(main,LINE," \t\n","}]"))
            {
                if(LINE==")")break;
                else
                {
                    std::string tag=LINE;
                    getWord(main,LINE," \t\n","}]");
                    addLoadVariable(tag,LINE);
                }
            }
        }

    }
}
void loadContent(std::string contentname)
{
    loadContentFile("main",contentname);
}
