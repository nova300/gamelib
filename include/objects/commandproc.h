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
    virtual std::string CmdName() { return std::string("** UNDEFINED CMD **\n"); }
    virtual std::string CmdPrompt() { return std::string("ERROR: no command processor defined\n ** Press ENTER to continue ** "); };
    virtual std::string RunCommand(std::string command, Program *prg) 
    { 
        prg->GetStack()->Pop();
        return std::string("\n") + CmdPrompt(); 
    };
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
    std::string CmdName() override { return text; };
    std::string CmdPrompt() override { return std::string("\n ** Press ENTER to continue ** "); };
    std::string RunCommand(std::string command, Program *prg) override;
};

