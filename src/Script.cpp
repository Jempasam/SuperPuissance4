#include "Script.h"

void ScriptTarget::reset()
{
    X=Xbase; Y=Ybase; NUM=NUMbase;
    TEAM=TEAMbase;TYPE=TYPEbase;

}

namespace content
{
    std::vector<Script> scripts;
    std::vector<CommandGroup> functions;
}


