#pragma once

#include <vector>

#include "core/program.h"

class Game;

class ProgramStack
{
private:
    void IPush(Program *program);
    void IPop(void);
public:
    //ProgramStack();
    //static void UpdateAll(float deltaTime);
    void Push(Program *program);
    void Pop(void);
    
    void Switch(Program *program);
    
    void Update(float deltaTime);
    //void PostUpdate(float deltaTime);
    void Render();
    Program *GetTop(void);
    void Reload();
    void Clear(void);
    void Clean(void);
    int ProgramsRunning();
    int ProgramsCapacity();
    bool Stop();
    enum State
    {
        NORMAL,
        FADEIN,
        FADEOUT,
        STOP
    };
    State GetState()
    {
        return state;
    }
private:
    std::vector<Program*> programStack;
    bool clear = false;
    bool stop = false;
    bool popnext = false;
    Program *nextProgram = NULL;
    State state;
public:

};