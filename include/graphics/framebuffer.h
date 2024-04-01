#pragma once

#include <raylib.h>
#include "core/object.h"

class FrameBuffer : public Object
{
public:
    FrameBuffer(int width = 320, int height = 200, int marginX = 30, int marginY = 30);
    ~FrameBuffer();
    void Render();
    void Begin();
    void End();
    Vector2 ScreenToCanvas(Vector2 pos);

private:
    RenderTexture2D fb;
    int width;
    int height;
    int marginX;
    int marginY;
};