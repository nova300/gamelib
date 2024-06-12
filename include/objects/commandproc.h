#pragma once
#include <string>
#include "core/program.h"
#include "core/programstack.h"

constexpr unsigned int hash(const char *s, int off = 0) 
{                        
    return !s[off] ? 5381 : (hash(s, off+1)*33) ^ s[off];                           
}

class CommandProcessor
{
public:
    virtual void Update(std::ostream& stream, Program *prg);
    virtual std::string CmdName() { return std::string("LIBGAME V.2\nCOPYRIGHT 2024 M.FAGERSTROM\n"); }
    virtual std::string CmdPrompt() { return std::string("> "); }
    virtual std::string RunCommand(std::string command, Program *prg) { return std::string("NO INTERPRETER\n") + CmdPrompt(); };
    virtual ~CommandProcessor() {};

private:
    std::string currentLine;
    bool init = false;
    float timer = 0.0f;
};

class CmdMessage : public CommandProcessor
{
private:
    std::string text;
public:
    CmdMessage(std::string msg) { text = msg; };
    std::string CmdName() { return text; };
    std::string CmdPrompt() { return std::string("\n-- PRESS ENTER TO EXIT --"); };
    std::string RunCommand(std::string command, Program *prg) override;
};

