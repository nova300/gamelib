#include "core/program.h"


ProgramStack* Program::GetStack()
{
    return this->stack;
}

RenderQueue* Program::GetQueue()
{
    return &this->renderQueue;
}