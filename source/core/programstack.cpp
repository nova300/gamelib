#include "core/programstack.h"

#include <stdio.h>
#include <typeinfo>
#include <iostream>
#include <objects/commandproc.h>
#include "objects/console.h"

bool ProgramStack::Stop()
{
    return stop;
}

int ProgramStack::ProgramsRunning()
{
    return programStack.size();
}

int ProgramStack::ProgramsCapacity()
{
    return programStack.capacity();
}

void ProgramStack::IPush(Program *program)
{
    stop = false;
    if (!programStack.empty()) programStack.back()->active = false;
    programStack.push_back(program);
    program->stack = this;
    program->Init();
}

void ProgramStack::IPop()
{
    if (programStack.empty()) return;
    Program *top = programStack.back();
    top->Destroy();
    delete top;
    programStack.pop_back();
    if (!programStack.empty()) programStack.back()->active = true;
}

void ProgramStack::Push(Program *program)
{
    if(!program)
    {
        std::cout << "PROGRAMSTACK: next program is NULL, stopping execution..." << std::endl;
        nextProgram = NULL;
        state = STOP;
        return;
    }
    std::cout << "PROGRAMSTACK: pushing to : " << typeid(*program).name() << std::endl;
    if(programStack.empty())
    {
        state = FADEIN;
        IPush(program);
        return;
    }

    nextProgram = program;
    state = FADEOUT;
}

void ProgramStack::Pop()
{
    nextProgram = NULL;
    popnext = true;
    state = FADEOUT;
}

void ProgramStack::Switch(Program *program)
{
    //if(state == FADEOUT) return;
    if(!program)
    {
        std::cout << "PROGRAMSTACK: next program is NULL, stopping execution..." << std::endl;
        nextProgram = NULL;
        state = STOP;
        return;
    }
    std::cout << "PROGRAMSTACK: switching to : " << typeid(*program).name() << std::endl;
    if(programStack.empty())
    {
        state = FADEIN;
        IPush(program);
        return;
    }

    nextProgram = program;
    popnext = true;
    state = FADEOUT;
}

void ProgramStack::Update(float deltaTime)
{
    if(programStack.empty()) return;

    if (state != FADEOUT || state != STOP) // dont update if fading out
    {
        GetTop()->Update(deltaTime);
        GetTop()->PostUpdate(deltaTime);
    } 

    GetTop()->SoftRender();

    for (auto &p : programStack)
    {
        p->ConstantUpdate(deltaTime);
    }

}

void ProgramStack::Render()
{
    if(programStack.empty())
    {
        if(state == STOP) stop = true;
        return;
    }

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
        if(GetTop()->FadeOut())
        {
            printf("PROGRAMSTACK: fadeout done\n");

            if(popnext)
            {
                IPop();
                popnext = false;
            }

            state = FADEIN;
            
            if(nextProgram == NULL) 
            {
                if(programStack.empty())
                {
                    printf("PROGRAMSTACK: cant find next program, Goodbye!\n");
                    state = STOP;
                    stop = true;
                }
            }
            else
            {
                IPush(nextProgram);
                nextProgram = NULL;
            }
        }
        break;

    case STOP:
        if(GetTop()->FadeOut())
        {
            IPop();
            stop = true;
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
        IPop();
    }
}

void ProgramStack::Reload()
{
    popnext = true;
    nextProgram = NULL;
    state = FADEOUT;
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