#include "utils.h"
#include <raylib.h>
#include <cstring>
#include <algorithm>



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

float sign(float val)
{
    if(value < 0) return -1.0f;
    return 1.0f;
}

Color GetHueColor(float v)
{
    v = fmodf(v * 50.0f, 360.0f);
    return ColorFromHSV(v, 1.0f, 1.0f);
}

bool string_compare(const char* ctstr, const char* compstring)
{
    if (strstr(ctstr, compstring) != NULL)
    {
        return true;
    }
    return false;
}

Vector2 smooth_towards(float curr, float target, float duration, float curr_velocity)
{
	float deltaTime = GetFrameTime();
	float smooth_speed = 2 / std::max<float>(0.0001, duration);
	
	float x = smooth_speed * deltaTime;
	float e = 1 / (1 + x + 0.48 * x * x + 0.235 * x * x * x);
	float offset = curr - target;
	
	float temp = (curr_velocity + smooth_speed * offset) * deltaTime;
	curr_velocity = (curr_velocity - smooth_speed * temp) * e;
	float output = target + (offset + temp) * e;
	
	if ((target-curr > 0) == (output > target))
    {
        output = target;
		curr_velocity = (output - target) / deltaTime;
    }

	return Vector2{output, curr_velocity};
}