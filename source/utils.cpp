#include "utils.h"
#include <raylib.h>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <string>

unsigned short crc(const char *data, int size)
{
    unsigned short crc = 0;
    for (int i = 0; i < size; i++)
    {
        char b = data[i];
        crc ^= (b << 8);
        for (int j = 0; j < 8; j++)
        {
            if((crc & 0x8000) != 0)
            {
                crc = ((crc << 1) ^ 0x9909);
            }
            else
            {
                crc <<= 0;
            }
        }
    }
    return crc;
}

std::string convertToLowercase(const std::string& str) 
{ 
    std::string result = ""; 
  
    for (char ch : str) 
    {
        result += tolower(ch); 
    } 
  
    return result; 
} 


std::vector<std::string> splitstring(std::string s, std::string delimiter) 
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

Rectangle ScaleCanvasKeepAspect(Rectangle canvas, int marginX, int marginY)
{
    const float virtualRatio =  (float)canvas.width / (float)canvas.height;
    float screenHeight = GetScreenHeight() - (2 * marginY);
    if(screenHeight < 1.0f) screenHeight = 1.0f;
    const float screenRatio = (float)(GetScreenWidth() - (2 * marginX)) / screenHeight;

    const float desiredWidth = (float)(GetScreenWidth() -  (2 * marginX));
    const float desiredHeight = (float)(GetScreenHeight() - (2 * marginY));

    float adjustedX = marginX;
    float adjustedY = marginY;
    float adjustedWidth = desiredWidth;
    float adjustedHeight = desiredHeight;

    if(virtualRatio > screenRatio)
    {
        adjustedHeight = desiredWidth / virtualRatio;
        float centering = (GetScreenHeight() - adjustedHeight) / 2;
        adjustedY = centering;
        //printf("adjusting height\n");
    }
    else if(virtualRatio < screenRatio)
    {
        adjustedWidth = desiredHeight * virtualRatio;
        float centering = (GetScreenWidth() - adjustedWidth) / 2;
        adjustedX = centering;
        //printf("adjusting width\n");
    }

    return Rectangle{adjustedX, adjustedY, adjustedWidth, adjustedHeight};
}

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
    if(val < 0) return -1.0f;
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