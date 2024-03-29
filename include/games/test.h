#pragma once

#include "core/program.h"
#include "core/objectstore.h"
#include "graphics/renderqueuesorted2d.h"
#include "graphics/transition.h"

class TestProgram : public Program, public ObjectStore
{
public:
    void Init() override;
    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override;
    void Render() override;
    void Destroy() override;

    bool FadeIn() override;
    bool FadeOut() override;

    FadeTransition trans = FadeTransition(2.0f, BLACK);
    
    Object player;
    Camera2D camera;
    RenderQueueSorted2D rq = RenderQueueSorted2D(&camera, 0);
};