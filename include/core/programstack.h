#pragma once

#include <vector>

#include "core/program.h"

class ProgramStack
{
public:
    void Push(Program *program);
    void Pop(void);
    void Update(float deltaTime);
    void Render(void);
    Program *GetTop(void);
    void Reload(Program* start);
    void Clear(void);
    void Clean(void);
private:
    std::vector<Program*> programStack;
    bool clear = false;
    Program *nextProgram = NULL;
public:

};