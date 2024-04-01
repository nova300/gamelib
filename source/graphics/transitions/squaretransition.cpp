#include "graphics/transition.h"
#include <raymath.h>


SquareTransition::SquareTransition(float TIME, Color COLOR, int WIDTH, int HEIGHT)
{
    time = TIME;
    color = COLOR;
    width = WIDTH;
    height = HEIGHT;
    canvas = LoadRenderTexture(WIDTH, HEIGHT);
}

SquareTransition::~SquareTransition()
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



void SquareTransition::Update(int x, int y)
{
    if(x == -1) x = width / 2;
    if(y == -1) y = height / 2;
    BeginTextureMode(canvas);
        
        ClearBackground(color);
        //DrawRectangle(0.0f, 0.0f, width, height, BLACK);
        BeginBlendMode(BLEND_SUBTRACT_COLORS);
        //DrawCircle(x, y, currentRadius, color);
        DrawRectangle(x - currentWidth, y - currentHeight, currentWidth * 2, currentHeight * 2, color);

        EndBlendMode();

    EndTextureMode();
}

bool SquareTransition::FadeIn()
{
    if(intimer < time)
    {
        intimer += GetFrameTime();
        float alpha = intimer / time;
        currentWidth = (width / 2) * alpha;
        currentHeight = (height / 2) * alpha;
        currentWidth += currentWidth / 4;
        currentHeight += currentHeight / 4;
        DrawTexturePro(canvas.texture, Rectangle{0.0f, 0.0f, (float)width, (float)-height}, ScaleCanvasKeepAspect(Rectangle{0.0f, 0.0f, (float)width, (float)height}, 30, 20), Vector2Zero(), 0.0f, WHITE);
        return false;
    }
    return true;
}

bool SquareTransition::FadeOut()
{
    if(outtimer < time)
    {
        outtimer += GetFrameTime();
        float alpha = 1 - (outtimer / time);
        currentWidth = (width / 2) * alpha;
        currentHeight = (height / 2) * alpha;
        currentWidth += currentWidth / 4;
        currentHeight += currentHeight / 4;
        DrawTexturePro(canvas.texture, Rectangle{0.0f, 0.0f, (float)width, (float)-height}, ScaleCanvasKeepAspect(Rectangle{0.0f, 0.0f, (float)width, (float)height}, 30, 20) , Vector2Zero(), 0.0f, WHITE);
        return false;
    }
    return true;
}