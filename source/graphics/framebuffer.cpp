#include "graphics/framebuffer.h"

static Rectangle ScaleCanvasKeepAspect(Rectangle canvas, int marginX, int marginY)
{
    const float virtualRatio =  (float)canvas.width / (float)canvas.height;
    float screenHeight = GetScreenHeight();
    if(screenHeight < 1.0f) screenHeight = 1.0f;
    const float screenRatio = (float)GetScreenWidth() / screenHeight;

    const float desiredWidth = (float)(GetScreenWidth() -  2 * marginX);
    const float desiredHeight = (float)(GetScreenHeight() - 2 * marginY);

    float adjustedX = marginX;
    float adjustedY = marginY;
    float adjustedWidth = desiredWidth;
    float adjustedHeight = desiredHeight;

    if(virtualRatio > screenRatio)
    {
        adjustedHeight = desiredWidth / virtualRatio;
        float centering = (GetScreenHeight() - adjustedHeight) / 2;
        adjustedY = centering;
        //printf("adjusting height\n");
    }
    else if(virtualRatio < screenRatio)
    {
        adjustedWidth = desiredHeight * virtualRatio;
        float centering = (GetScreenWidth() - adjustedWidth) / 2;
        adjustedX = centering;
        //printf("adjusting width\n");
    }

    return Rectangle{adjustedX, adjustedY, adjustedWidth, adjustedHeight};
}

Vector2 FrameBuffer::ScreenToCanvas(Vector2 POS)
{
    const auto screenCanvas = ScaleCanvasKeepAspect(Rectangle{0.0f, 0.0f, (float)width, (float)height}, marginX, marginY);

    Vector2 out = POS;

    out.x -= screenCanvas.x;
    out.y -= screenCanvas.y;

    out.x /= screenCanvas.width;
    out.y /= screenCanvas.height;
    out.x *= width;
    out.y *= height;

    return out;
}

FrameBuffer::FrameBuffer(int WIDTH, int HEIGHT, int MARGINX, int MARGINY)
{
    fb = LoadRenderTexture(width, height);
    width = WIDTH;
    height = HEIGHT;
    marginX = MARGINX;
    marginY = MARGINY;
}

FrameBuffer::~FrameBuffer()
{
    if(IsRenderTextureReady(fb)) UnloadRenderTexture(fb);
}

void FrameBuffer::Begin()
{
    BeginTextureMode(fb);
}

void FrameBuffer::End()
{
    EndTextureMode();
}

void FrameBuffer::Render()
{
    DrawTexturePro(fb.texture, Rectangle{0.0f, 0.0f, (float)width, (float)-height}, ScaleCanvasKeepAspect(Rectangle{0.0f, 0.0f, (float)width, (float)height}, marginX, marginY) , Vector2Zero(), 0.0f, WHITE);
}