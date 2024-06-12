#pragma once

#include "core/behaviour.h"
#include <raylib.h>
#include <string>
#include "graphics/texturecache.h"

class Sprite : public Behaviour
{
public:
    ~Sprite() {};
    void Load(std::shared_ptr<CTexture> tex);
    void Load(std::string path);
    void Load(Texture2D texture);

    void Render() override;

    Color color = WHITE;
private:
    std::shared_ptr<CTexture> texture;
    Texture2D unmanagedTexture;
    bool managed = true;
    Rectangle src;
    float width = 32.0f;
    float height = 32.0f;
};