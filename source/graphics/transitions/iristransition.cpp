#include "graphics/transition.h"
#include <raymath.h>


IrisTransition::IrisTransition(float TIME, Color COLOR, int WIDTH, int HEIGHT, Vector2 target)
{
    time = TIME;
    color = COLOR;
    width = WIDTH;
    height = HEIGHT;
    targetX = target.x;
    targetY = target.y;
    canvas = LoadRenderTexture(WIDTH, HEIGHT);
}

IrisTransition::~IrisTransition()
{
    UnloadRenderTexture(canvas);
}

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

void IrisTransition::Update(int x, int y)
{
    if(x == -1) x = targetX;
    if(y == -1) y = targetY;
    BeginTextureMode(canvas);
        
        ClearBackground(color);
        //DrawRectangle(0.0f, 0.0f, width, height, BLACK);
        BeginBlendMode(BLEND_SUBTRACT_COLORS);
        DrawCircle(x, y, currentRadius, color);

        EndBlendMode();

    EndTextureMode();
}

bool IrisTransition::FadeIn()
{
    if(intimer < time)
    {
        intimer += GetFrameTime();
        float alpha = intimer / time;
        currentRadius = (width / 2) * alpha;
        currentRadius += currentRadius / 4;
        DrawTexturePro(canvas.texture, Rectangle{0.0f, 0.0f, (float)width, (float)-height}, ScaleCanvasKeepAspect(Rectangle{0.0f, 0.0f, (float)width, (float)height}, 50, 50), Vector2Zero(), 0.0f, WHITE);
        return false;
    }
    intimer = 0.0f;
    return true;
}

bool IrisTransition::FadeOut()
{
    if(outtimer < time)
    {
        outtimer += GetFrameTime();
        float alpha = 1 - (outtimer / time);
        currentRadius = (width / 2) * alpha;
        currentRadius += currentRadius / 4;
        DrawTexturePro(canvas.texture, Rectangle{0.0f, 0.0f, (float)width, (float)-height}, ScaleCanvasKeepAspect(Rectangle{0.0f, 0.0f, (float)width, (float)height}, 50, 50) , Vector2Zero(), 0.0f, WHITE);
        return false;
    }
    outtimer = 0.0f;
    return true;
}