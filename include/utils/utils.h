#pragma once
#include <map>
#include <vector>
#include <raylib.h>
#include <cstddef>
#include <string>
#include <set>

bool string_compare(const char* ctstr, const char* compstring);

Rectangle ScaleCanvasKeepAspect(Rectangle canvas, int marginX, int marginY);

unsigned short crc(const char *data, int size = 24);

std::vector<std::string> splitstring(std::string s, std::string delimiter);

Vector2 smooth_towards(float curr, float target, float duration, float curr_velocity);

Color GetRandomColor();

Color GetHueColor(float v);

float sign(float val);

std::string convertToLowercase(const std::string& str);

template<typename T>
std::pair<T, T> Shuffle(T t1, T t2)
{
    int r = GetRandomValue(0, 1);
    switch (r)
    {
    case 1:
        return std::make_pair(t2, t1);
        break;
    
    default:
        return std::make_pair(t1, t2);
        break;
    }
}

