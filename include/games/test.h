#pragma once

#include "core/program.h"
#include "core/objectstore.h"
#include "graphics/renderqueue.h"

class TestProgram : public Program
{
public:
    void Init() override;
    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override;
    void Render() override;
    void Destroy() override;
    
    ObjectStore os1;

    std::shared_ptr<Object> player;
};