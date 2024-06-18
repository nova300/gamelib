#pragma once

#include <raylib.h>
#include <vector>
#include <memory>

#include "utils.h"
#include "core/object.h"
#include "graphics/textureatlas.h"

struct Tile
{
    bool solid = false;
    Rectangle src;
    std::shared_ptr<CTexture> texture;
    Color color = BLACK;
};

class TileMap : public Map2D<Tile>
{
public:

    void Update(float deltaTime);
    void Render();

private:
    std::vector<std::shared_ptr<TextureAtlas>> tileGraphics;
};