#pragma once
#include <map>
#include <vector>
#include <raylib.h>
#include <cstddef>
#include <string>
#include <set>

struct IntRectangle
{
    int x;
    int y;
    int width;
    int height;
    IntRectangle() {};
    IntRectangle(Rectangle floats)
    {
        x = (int)floats.x;
        y = (int)floats.y;
        width = (int)floats.width;
        height = (int)floats.height;
    }
};