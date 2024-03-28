#include "utils.h"
#include <raylib.h>

Color GetRandomColor()
{
    int rand = GetRandomValue(0, 5);

    switch (rand)
    {
    case 0:
        return RED;
        break;
    case 1:
        return GREEN;
        break;
    case 2:
        return ORANGE;
        break;
    case 3:
        return VIOLET;
        break;
    case 4:
        return PINK;
        break;
    default:
        return BLUE;
        break;
    }  
}

Color GetHueColor(float v)
{
    v = fmodf(v * 50.0f, 360.0f);
    return ColorFromHSV(v, 1.0f, 1.0f);
}