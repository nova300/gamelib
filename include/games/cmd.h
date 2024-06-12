#pragma once

#include "core/program.h"
#include "objects/commandproc.h"

class CmdProgram : public Program
{
public:
    ~CmdProgram() {};
    void Init() override;
    void Update(float deltaTime) override;
    void SoftRender() override;
    void Render() override;

    Console console;
    CommandProcessor cmd;
    
};