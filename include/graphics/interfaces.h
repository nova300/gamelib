#pragma once
#include <raylib.h>
#include <vector>

namespace Graphics
{
    class IRenderable
    {
    public:
        virtual void Render() = 0;
        virtual Rectangle GetRenderBounds() = 0;
    };

    struct Sprite
    {
        Texture texture;
        Rectangle src;
        Rectangle dst;
        Color color;
    };

    class IHaveSprites
    {
    public:
        virtual std::vector<Sprite> CollectSprites() = 0;
    };

};