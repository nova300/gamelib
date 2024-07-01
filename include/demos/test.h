#pragma once

#include "core/program.h"
#include "core/objectstore.h"
#include "graphics/renderqueuesorted2d.h"
#include "graphics/transition.h"
#include "gui/gui.h"



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

    virtual RenderQueue* GetRenderQueue(int index) override;

    bool FadeIn() override;
    bool FadeOut() override;

    IrisTransition trans = IrisTransition(2.0f, DARKBLUE, 160, 100);

    RenderTexture2D canvas;
    
    int canvaswidth = 320;
    int canvasheight = 200;
    int marginX = 30;
    int marginY = 20;
    
    std::shared_ptr<Object> player;
    std::shared_ptr<Object> map;
    std::shared_ptr<Object> window1;
    Camera2D camera;
    RenderQueueSorted2D rq = RenderQueueSorted2D(&camera);
    WindowManager wm;
};