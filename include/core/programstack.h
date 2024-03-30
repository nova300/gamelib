#pragma once

#include <vector>

#include "core/program.h"

class Game;

class ProgramStack
{
public:
    //ProgramStack();
    //static void UpdateAll(float deltaTime);
    void Push(Program *program);
    void Switch(Program *program);
    void Pop(void);
    void Update(float deltaTime);
    void PostUpdate(float deltaTime);
    void Render();
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