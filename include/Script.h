#ifndef SCRIPT_H
#define SCRIPT_H

#include <vector>
#include <string>
#include <iostream>

enum command
{
    move=0,
    setObjectTex=1,
    setStateTex=2,
    setState=3,
    setObject=4,
    ifObject=5,
    ifState=6,
    ifOneObject=7,
    ifOneState=8,
    ifOneOutside=9,
    ifOneInside=10,
    ifKeyPressed=11,
    ifSomeoneKeyPressed=12,
    setpos=13,
    variableset=14,
    ifall=15,
    setcgroup=16,
    settimer=17,
    breek=18,
    globalvarset=19,
    setmenu=20,
    usefunction=21
};
enum ModifierType
{
    pos1=0,
    offset1=1,
    team1=2,
    num1=3
};
enum ArgumentType
{
    value=0,
    tag=1,
    var=2,
    dynamic=3,
    iflength=4,
    varnum=5,
    globalvar=6,
    globalvarnum=7,
    objectvar=8
};
// STATE=0 STATES=1 TYPE=2 TYPES=3 CURSORX=4 CURSORY=5 TIMER=6 CGROUP=7 WORLDSIZEX=8 WORLDSIZEY=9
// WINDOWWIDTH=10 WINDOWHEIGHT=11 DIDASSOCIATE=12 ISOUTSIDE=13
enum ArgOperator
{
    plus=0,
    minus=1,
    multiply=2,
    divide=3,
    pushback=4,
    et=5,
    ou=6,
    xou=7,
    elementstart=8,
    elementend=9
};
struct ScriptTarget
{
    int X=0,Y=0,NUM=0;
    int TEAM=0;int TYPE;

    int Xbase=0,Ybase=0,NUMbase=0;
    int TEAMbase=0;int TYPEbase;

    int identifier=0;

    void reset();
};
struct Modifier;
struct Value
{
    std::vector<int> value;
    ArgOperator operat;
    ArgumentType type;
    std::vector<Modifier> modifiers;
};
struct Argument
{
    std::vector<Value> values;
};
struct Modifier
{
    ModifierType type;
    std::vector<Argument> arguments;
};
struct Command
{
    command command;
    std::vector<Argument> argument;
    std::vector<Modifier> modifiers;
};
struct CommandGroup
{
    std::vector<Command> commands;
    int duration;
};
struct Script
{
    std::vector<CommandGroup> commandGroup;
    Script(): commandGroup()
    {

    }
    Script(const Script &b)
    {
        commandGroup=b.commandGroup;
    }
};



namespace content
{
    extern std::vector<Script> scripts;
    extern std::vector<CommandGroup> functions;
}

#endif // SCRIPT_H
