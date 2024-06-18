//register programs here
//compiled in objects/debugconsole.cpp

//include statements here
#include "demos/cmd.h"
#include "demos/test.h"

//registation function here
void DebugConsole::RegisterPrograms()
{
    REGISTER_CLASS(Terminal);
    REGISTER_CLASS(TestProgram);
}