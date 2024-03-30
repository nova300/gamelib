#pragma once

#include <raylib.h>
#include <string>
#include <memory>

#include "graphics/animatedsprite.h"
#include "graphics/texturecache.h"

class TextureAtlas
{
public:
    TextureAtlas(std::string path, int cellwidth, int cellheight);
    Rectangle GetDrawRect(int index);
    Rectangle GetDrawUVS(int index);
    std::shared_ptr<CTexture> GetBaseTexture();
    SpriteFrame GetSpriteFrame(int index, float time = 0.1f, Color color = WHITE);

private:
    std::shared_ptr<CTexture> texture;
    int cellwidth;
    int cellheight;
    int hsize;
    int vsize;
    Rectangle clip;
};