#pragma once

#include <raylib.h>
#include <vector>
#include <memory>

#include "core/object.h"
#include "graphics/textureatlas.h"

struct TileMapData
{
    
};

struct TileDef
{
    int id;
    int gfxId;
    bool solid;

};


class TileMap : public Object
{
public:
    void Load(int posX, int posY, std::)

private:
    std::vector<std::shared_ptr<TextureAtlas>> tileGraphics;
};