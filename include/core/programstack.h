#pragma once

#include <vector>

#include "core/program.h"

class ProgramStack
{
public:
    void Push(Program *program);
    void Switch(Program *program);
    void Pop(void);
    void Update(float deltaTime);
    void Render(void);
    Program *GetTop(void);
    void Reload(Program* start);
    void Clear(void);
    void Clean(void);
    enum State
    {
        NORMAL,
        FADEIN,
        FADEOUT
    };
    State GetState()
    {
        return state;
    }
private:
    std::vector<Program*> programStack;
    bool clear = false;
    Program *nextProgram = NULL;
    State state;
public:

};