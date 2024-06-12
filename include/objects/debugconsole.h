#pragma once
#include <string>
#include "core/programstack.h"
#include "objects/console.h"
#include "graphics/transition.h"
#include "objects/commandproc.h"

class DebugConsole : public CommandProcessor
{
public:
    ~DebugConsole() {};
    std::string RunCommand(std::string command, Program *prg);
    std::string CmdName() { return std::string("LIBGAME DEBUG CONSOLE V.2"); };
    std::string CmdPrompt() { return std::string("DEBUG> "); }
    static void RegisterPrograms();

};


