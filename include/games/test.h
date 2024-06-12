#pragma once

#include "core/program.h"
#include "core/objectstore.h"
#include "graphics/renderqueuesorted2d.h"
#include "graphics/transition.h"



class TestProgram : public Program
{
public:
    ~TestProgram() {};
    void Init() override;
    void Update(float deltaTime) override;
    void PostUpdate(float deltaTime) override;
    void SoftRender() override;
    void Render() override;
    void Destroy() override;

    bool FadeIn() override;
    bool FadeOut() override;

    IrisTransition trans = IrisTransition(2.0f, DARKBLUE, 160, 100);

    RenderTexture2D canvas;
    
    int canvaswidth = 320;
    int canvasheight = 200;
    int marginX = 30;
    int marginY = 20;
    
    Object player;
    Object map;
    Camera2D camera;
    RenderQueueSorted2D rq = RenderQueueSorted2D(&camera);
    ObjectStore os;

    
};