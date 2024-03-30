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
    void PostUpdate(float deltaTime) override;
    void Render() override;
    void Destroy() override;

    bool FadeIn() override;
    bool FadeOut() override;

    FadeTransition trans = FadeTransition(2.0f, BLACK);

    RenderTexture2D canvas;
    
    int canvaswidth = 256;
    int canvasheight = 224;
    int marginX = 60;
    int marginY = 50;
    
    Object player;
    Camera2D camera;
    RenderQueueSorted2D rq = RenderQueueSorted2D(&camera);

    
};