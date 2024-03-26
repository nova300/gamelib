#pragma once

#include "core/behaviour.h"
#include <raylib.h>
#include <string>

class Sprite : public Behaviour
{
public:
    Sprite(Object* obj) : Behaviour(obj) {};
    void Load(Texture2D TEX);
    void Load(std::string path);

    void Render() override;

    Color color = WHITE;
private:
    Texture2D texture;
    Rectangle src;
    float width = 32.0f;
    float height = 32.0f;
};