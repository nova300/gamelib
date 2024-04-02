#pragma once
#include <map>
#include <vector>
#include <raylib.h>
#include <cstddef>

bool string_compare(const char* ctstr, const char* compstring);

Vector2 smooth_towards(float curr, float target, float duration, float curr_velocity);

Color GetRandomColor();

Color GetHueColor(float v);

float sign(float val);

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

template<typename T>
class Map2D
{
private:
    std::map<std::pair<int, int>, T> map;

public:
    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        UPLEFT,
        UPRIGHT,
        DOWNLEFT,
        DOWNRIGHT
    };
    Map2D()
    {

    }

    T& GetRef(int x, int y)
    {
        auto vec = std::pair<int, int>(x, y);
        if (map.count(vec) > 0)
        {
            T &t = map.at(vec);
            return t;
        }
        map[vec] = T();
        return map.at(vec);
    }

    T* Get(int x, int y)
    {
        auto vec = std::pair<int, int>(x, y);
        if (map.count(vec) > 0)
        {
            return &(map[vec]);
        }
        return NULL;
    }

    void Set(int x, int y, T value)
    {
        map.emplace(std::pair<int, int>(x, y), value);
    }

    std::map<Direction,T*> GetNeighbors(const int x, const int y)
    {
        std::map<Direction, T*> neighbors;
        neighbors[UP] = Get(x, y - 1);
        neighbors[DOWN] = Get(x, y + 1);
        neighbors[LEFT] = Get(x - 1, y);
        neighbors[RIGHT] = Get(x + 1, y);
        neighbors[UPLEFT] = Get(x - 1, y - 1);
        neighbors[UPRIGHT] = Get(x + 1, y - 1);
        neighbors[DOWNLEFT] = Get(x - 1, y + 1);
        neighbors[DOWNRIGHT] = Get(x + 1, y + 1);
        
        return neighbors;
    }

    std::map<Direction,T*> GetCardinalNeighbors(const int x, const int y)
    {
        std::map<Direction, T*> neighbors;
        neighbors[UP] = Get(x, y - 1);
        neighbors[DOWN] = Get(x, y + 1);
        neighbors[LEFT] = Get(x - 1, y);
        neighbors[RIGHT] = Get(x + 1, y);

        std::map<Direction, T*> neighbors2;

        for (auto [dir, ptr] : neighbors)
        {
            if(ptr != NULL)
            {
                neighbors2[dir] = ptr;
            }
        }

        return neighbors2;
    }

};