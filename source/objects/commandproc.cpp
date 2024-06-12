#include "objects/commandproc.h"
#include <raylib.h>
#include <iostream>
#include "utils.h"
#include <string>
#include <sstream>


void CommandProcessor::Update(std::ostream& stream, Program *prg)
{
    if(!init)
    {
        if(timer > 0.5f)
        {
            stream.flush();
            stream << std::endl << CmdName() << std::endl;
            stream << CmdPrompt();
            currentLine.clear();
            stream.flush();
            init = true;
            timer = 0.0f;
            return;
        }
        timer += GetFrameTime();
        return;
    }
    if(IsKeyPressed(KEY_BACKSPACE))
    {
        if(!currentLine.empty())
        {
            stream << '\b';
            currentLine.pop_back();
            stream.flush();
        }
    }

    if(IsKeyPressed(KEY_ENTER))
    {
        stream << std::endl;
        stream << RunCommand(currentLine, prg);
        //stream << CmdPrompt();
        currentLine.clear();
        stream.flush();
    }

    char c = GetCharPressed();
    if(c != 0)
    {
        stream << c;
        currentLine.push_back(c);
        stream.flush();
    }
}

std::string CmdMessage::RunCommand(std::string command, Program *prg)
{
    prg->GetStack()->Pop();
    return std::string("Goodbye!\n"); 
}