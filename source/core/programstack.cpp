#include "core/programstack.h"

void ProgramStack::Push(Program *program)
{
    if (!programStack.empty()) programStack.back()->Sleep();
    programStack.push_back(program);
    program->stack = this;
    program->Init();
}

void ProgramStack::Pop()
{
    if (programStack.empty()) return;
    Program *top = programStack.back();
    top->Destroy();
    delete(top);
    programStack.pop_back();
    if (!programStack.empty()) programStack.back()->Wake();
}

void ProgramStack::Update(float deltaTime)
{
    if(programStack.empty()) return;
    for(auto& p : programStack)
    {
        p->Update(deltaTime);
    }

    for(auto& p : programStack)
    {
        p->LateUpdate(deltaTime);
    }
}

void ProgramStack::Render()
{
    if(programStack.empty()) return;
    for(auto& p : programStack)
    {
        p->Render();
    }
}

Program *ProgramStack::GetTop()
{
    if(programStack.empty()) return NULL;
    Program *top = programStack.back();
    return top;
}

void ProgramStack::Clear()
{
    while (!programStack.empty())
    {
        Pop();
    }
}

void ProgramStack::Reload(Program *start)
{
    clear = true;
    nextProgram = start;
}

void ProgramStack::Clean()
{
    switch (clear)
    {
    case true:
        clear = false;
        Clear();
        Push(nextProgram);
        break;
    
    default:
        break;
    }
}