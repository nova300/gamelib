#pragma once

#include <raylib.h>

class FadeTransition
{
public:
    FadeTransition(float time = 1.0f, Color color = BLACK);
    ~FadeTransition();
    bool FadeIn();
    bool FadeOut();
private:
    Color color;
    float time = 1.0f;
    float intimer = 0.0f;
    float outtimer = 0.0f;
};


class IrisTransition
{
public:
    IrisTransition(float time = 1.0f, Color color = BLACK, int width = 100, int height = 75, Vector2 target = Vector2{100.0f / 2.0f, 75.0f / 2.0f});
    ~IrisTransition();
    bool FadeIn();
    bool FadeOut();
    void Update(int x = -1, int y = -1);
private:
    RenderTexture2D canvas;
    Color color;
    float time = 1.0f;
    float intimer = 0.0f;
    float outtimer = 0.0f;
    int targetX;
    int targetY;
    int width;
    int height;
    float currentRadius = 0.0f;
};

class SquareTransition
{
public:
    SquareTransition(float time = 1.0f, Color color = BLACK, int width = 32, int height = 20);
    ~SquareTransition();
    bool FadeIn();
    bool FadeOut();
    void Update(int x = -1, int y = -1);
private:
    RenderTexture2D canvas;
    Color color;
    float time = 1.0f;
    float intimer = 0.0f;
    float outtimer = 0.0f;
    int targetX;
    int targetY;
    int width;
    int height;
    float currentWidth = 0.0f;
    float currentHeight = 0.0f;
};