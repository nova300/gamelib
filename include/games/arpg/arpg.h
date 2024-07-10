#pragma once

#include "core/program.h"
#include "core/objectstore.h"
#include "graphics/renderqueuesorted2d.h"
#include "graphics/transition.h"
#include "gui/gui.h"


namespace ARPG
{


class Overworld : public Program
{
public:
    virtual ~Overworld() {};
    void Init() override;
    void Update(float deltaTime) override;
    void PostUpdate(float deltaTime) override;
    void SoftRender() override;
    void Render() override;
    void Destroy() override;

    virtual RenderQueue* GetRenderQueue(int index) override;

    bool FadeIn() override;
    bool FadeOut() override;

    IrisTransition trans = IrisTransition(2.0f, BLACK, 160, 100);
    
    std::shared_ptr<Object> player;
    std::shared_ptr<Object> map;
    Camera2D camera;
    RenderQueueSorted2D rq = RenderQueueSorted2D(&camera);
    WindowManager wm;
};


class Player : public Object
{
public:
    virtual ~Player() {}
    
};



}