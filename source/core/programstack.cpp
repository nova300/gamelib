#include "core/programstack.h"

#include <stdio.h>
#include <typeinfo>
#include <iostream>
/*#include <set>

std::set<ProgramStack*> programStacks;

ProgramStack::ProgramStack()
{
    programStacks.emplace(this);
}

ProgramStack::~ProgramStack()
{
    programStacks.erase(this);
}

void ProgramStack::UpdateAll(float deltaTime)
{
    for(auto stk : programStacks)
    {
        stk->Update(deltaTime);
    }
}*/

void ProgramStack::Push(Program *program)

{
    if (!programStack.empty()) programStack.back()->active = false;
    programStack.push_back(program);
    program->stack = this;
    program->Init();
}

void ProgramStack::Pop()
{
    if (programStack.empty()) return;
    Program *top = programStack.back();
    top->Destroy();
    programStack.pop_back();
    if (!programStack.empty()) programStack.back()->active = true;
}

void ProgramStack::Switch(Program *program)
{
    //if(state == FADEOUT) return;
    std::cout << "PROGRAMSTACK: switching to : " << typeid(*program).name() << std::endl;
    if(programStack.empty())
    {
        state = FADEIN;
        Push(program);
        return;
    }

    nextProgram = program;
    state = FADEOUT;
}

void ProgramStack::Update(float deltaTime)
{
    if(programStack.empty()) return;


    if (state != FADEOUT) // dont update if fading out
    {
        for (auto &p : programStack)
        {
            p->Update(deltaTime);
        }

        for (auto &p : programStack)
        {
            p->PostUpdate(deltaTime);
        }
    } 


    for(auto& p : programStack)
    {
        p->SoftRender();
    }

}

void ProgramStack::Render()
{
    if(programStack.empty()) return;

    /*for(auto& p : programStack)
    {
        p->Render();
    }*/

    GetTop()->Render();

    switch (state)
    {
    case FADEIN:
        if(GetTop()->FadeIn())
        {
            printf("PROGRAMSTACK: fadein done\n");
            state = NORMAL;
        }
        break;
    
    case FADEOUT:
        if(nextProgram == NULL) 
        {
            state = NORMAL;
            printf("PROGRAMSTACK: FADEOUT set but no program is set to next");
        }
        if(GetTop()->FadeOut())
        {
            printf("PROGRAMSTACK: fadeout done\n");
            Pop();
            state = FADEIN;
            Push(nextProgram);
        }
        break;
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