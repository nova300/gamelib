#pragma once

#include "core/behaviour.h"
#include <raylib.h>
#include <string>
#include "graphics/texturecache.h"

class Sprite : public Behaviour
{
public:
    Sprite(Object* obj) : Behaviour(obj) {};
    void Load(std::shared_ptr<CTexture> tex);
    void Load(std::string path);

    void Render() override;

    Color color = WHITE;
private:
    std::shared_ptr<CTexture> texture;
    Rectangle src;
    float width = 32.0f;
    float height = 32.0f;
};