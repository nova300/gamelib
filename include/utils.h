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

class IPoolLifetime
{
public:
    virtual void PoolConstruct() = 0;
    virtual void PoolDestruct() = 0; 
};

template<typename T>
class PoolVector
{
private:
    struct Data
    {
        bool inUse;
        T value;
    };

    std::vector<Data> vector;

public:
    std::vector<Data>* GetVector()
    {
        return &vector;
    }

    T* Get(uint index)
    {
        if(index >= vector.size()) return nullptr;
        if(!vector[index].inUse) return nullptr;
        return &vector[index].value;
    }

    uint Add(T value)
    {

        if(std::is_base_of<IPoolLifetime, T>::value)
        {
            value.PoolConstruct();
        }

        for (int i = 0; i < vector.size() ; i++)
        {
            if(!vector[i].inUse)
            {
                vector[i].inUse = true;
                vector[i].value = value;
                return i;
            }
        }

        int index = vector.size();

        Data data = 
        {
            true,
            value
        };

        vector.push_back(data);

    }

    void Remove(uint index)
    {
        if(index <= vector.size()) return;
        if(std::is_base_of<IPoolLifetime, T>::value)
        {
            vector[index].value.PoolDestruct();
        }
        vector[index].inUse = false;  
    }

};



template<typename T>
class Map2D
{
public:
    struct Data
    {
        int x, y, w, h;
        T value;
    };
    
    using Position = std::pair<int, int>;
private:
    std::map<Position, std::set<uint>> map;
    PoolVector<Data> storage;

    std::vector<T*> Get(std::set<uint> idxes)
    {
        std::vector<T*> out;
        for(uint idx : idxes)
        {
            T* ptr = storage.Get(idx);
            if(ptr) out.push_back(ptr);
        }
        return out;
    }
    int cellSize = 32;
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
    Map2D(int CELLSIZE = 32)
    {
        cellSize = CELLSIZE;
    }

    std::vector<T*> Get(int x, int y)
    {
        x = x / cellSize;
        y = y / cellSize;
        auto vec = std::pair<int, int>(x, y);
        std::set<uint> idxes;
        if (map.count(vec) > 0)
        {
            for(uint idx : map[vec])
            {
                idxes.insert(idx);
            }
        }
        return Get(idxes);
    }

    std::vector<T*> Get(int X, int Y, int W, int H)
    {
        X = X / cellSize;
        Y = Y / cellSize;
        W = W / cellSize;
        H = H / cellSize;
        std::set<uint> idxes;
        for(int x = X; x < X + W; x++)
        {
            for(int y = Y; y < Y + H; y++)
            {
                auto p = Position(x, y);
                if (map.count(p) > 0)
                {
                    for (uint idx : map[p])
                    {
                        idxes.insert(idx);
                    };
                }
            }
        }
        return Get(idxes);
    }

    std::vector<T*> Get(uint index)
    {
        std::set<uint> indicies;
        Data *data = storage.Get(index);
        float X = data->x / cellSize;
        float Y = data->y / cellSize;
        float W = data->w / cellSize;
        float H = data->h / cellSize;
        if (data)
        {
            for (int x = X; x < X + W; x++)
            {
                for (int y = Y; y < Y + H; y++)
                {
                    auto p = Position(x, y);
                    if (map.count(p) > 0)
                    {
                        for (uint idx : map[p])
                        {
                            indicies.insert(idx);
                        };
                    }
                }
            }
        }

        return Get(indicies);
    }

    

    void Set(uint index, T value)
    {
        Data* ptr = storage.Get(index);
        if(ptr)
        {
            ptr->value = value;
        }
    }

    void Update(int x, int y, int w, int h, uint index)
    {
        Data* dat = storage.Get(index);
        if(dat == nullptr) return;
        Erase(dat->x, dat->y, dat->w, dat->h, index);
        Fill(x, y, w, h, index);
    }

    void Update(int x, int y, int w, int h, uint index, T value)
    {
        Set(index, value);
        Update(x, y, w, h, index);
    }

    uint Add(int x, int y, int w, int h, T value)
    {
        Data dat = 
        {
            x,
            y,
            w,
            h,
            value
        };
        uint index = storage.Add(value);
        Fill(x, y, w, h, index);

        return index;
    }

    void Remove(uint index)
    {
        Data *data = storage.Get(index);
        if(!data) return;
        Erase(data->x, data->y, data->w, data->h, index);
        storage.Remove(data);
    }

    void Fill(int X, int Y, int W, int H, uint index)
    {
        X = X / cellSize;
        Y = Y / cellSize;
        W = W / cellSize;
        H = H / cellSize;
        for(int x = X; x < X + W; x++)
        {
            for(int y = Y; y < Y + H; y++)
            {
                auto p = Position(x, y);
                if(map.count(p) > 0)
                {
                    map[p].insert(index);
                }
            }
        }
    }

    void Erase(int X, int Y, int W, int H, uint index)
    {
        X = X / cellSize;
        Y = Y / cellSize;
        W = W / cellSize;
        H = H / cellSize;
        for(int x = X; x < X + W; x++)
        {
            for(int y = Y; y < Y + H; y++)
            {
                auto p = Position(x, y);
                if(map.count(p) > 0)
                {
                    map[p].erase(index);
                }
            }
        }
    }

    std::map<Direction,std::vector<T*>> GetNeighbors(const int x, const int y)
    {
        std::map<Direction, std::vector<T*>> neighbors;
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

    std::map<Direction,std::vector<T*>> GetCardinalNeighbors(const int x, const int y)
    {
        std::map<Direction, std::vector<T*>> neighbors;
        neighbors[UP] = Get(x, y - 1);
        neighbors[DOWN] = Get(x, y + 1);
        neighbors[LEFT] = Get(x - 1, y);
        neighbors[RIGHT] = Get(x + 1, y);

        return neighbors;
    }

};

template<typename T>
class Map3D
{
public:
    struct Data
    {
        int x, y, z, w, h, d;
        T value;
    };
    
    using Position = std::tuple<int, int, int>;
private:
    std::map<Position, std::set<uint>> map;
    PoolVector<Data> storage;

    std::vector<T*> Get(std::set<uint> idxes)
    {
        std::vector<T*> out;
        for(uint idx : idxes)
        {
            T* ptr = storage.Get(idx);
            if(ptr) out.push_back(ptr);
        }
        return out;
    }

public:
    enum Direction
    {
        UP = 1 << 0,
        DOWN = 1 << 1,
        LEFT = 1 << 2,
        RIGHT = 1 << 3,
        FOWARD = 1 << 4,
        BACK = 1 << 5,
    };
    Map3D()
    {

    }

    std::vector<T*> Get(int x, int y, int z)
    {
        auto vec = Position(x, y, z);
        return Get(vec);
    }

    std::vector<T*> Get(Position vec)
    {
        std::set<uint> idxes;
        if (map.count(vec) > 0)
        {
            for(uint idx : map[vec])
            {
                idxes.insert(idx);
            }
        }
        return Get(idxes);
    }

    std::vector<T*> Get(int X, int Y, int Z, int W, int H, int D)
    {
        std::set<uint> idxes;
        for(int x = X; x < X + W; x++)
        {
            for(int y = Y; y < Y + H; y++)
            {
                for(int z = Z; z < Z + D; z++)
                {
                    auto p = Position(x, y, z);
                    if (map.count(p) > 0)
                    {
                        for (uint idx : map[p])
                        {
                            idxes.insert(idx);
                        };
                    }
                }
            }
        }
        return Get(idxes);
    }

    std::vector<T*> Get(uint index)
    {
        std::set<uint> indicies;
        Data *data = storage.Get(index);
        if (data)
        {
            for (int x = data->x; x < data->x + data->w; x++)
            {
                for (int y = data->y; y < data->y + data->h; y++)
                {
                    for(int z = data->z; z < data->z + data->d; z++)
                    {
                        auto p = Position(x, y, z);
                        if (map.count(p) > 0)
                        {
                            for (uint idx : map[p])
                            {
                                indicies.insert(idx);
                            };
                        }
                    }
                }
            }
        }

        return Get(indicies);
    }

    

    void Set(uint index, T value)
    {
        Data* ptr = storage.Get(index);
        if(ptr)
        {
            ptr->value = value;
        }
    }

    void Update(int x, int y, int z, int w, int h, int d, uint index)
    {
        Data* dat = storage.Get(index);
        if(dat == nullptr) return;
        Erase(dat->x, dat->y, dat->z, dat->w, dat->h, dat->d, index);
        Fill(x, y, z, w, h, d, index);
    }

    void Update(int x, int y, int z, int w, int h, int d, uint index, T value)
    {
        Set(index, value);
        Update(x, y, z, w, h, d, index);
    }

    uint Add(int x, int y, int z, int w, int h, int d, T value)
    {
        Data dat = 
        {
            x,
            y,
            z,
            w,
            h,
            d,
            value
        };
        uint index = storage.Add(value);
        Fill(x, y, z, w, h, d, index);

        return index;
    }

    void Remove(uint index)
    {
        Data *data = storage.Get(index);
        if(!data) return;
        Erase(data->x, data->y, data->z, data->w, data->h, data->d, index);
        storage.Remove(data);
    }

    void Fill(int X, int Y, int Z, int W, int H, int D, uint index)
    {
        for(int x = X; x < X + W; x++)
        {
            for(int y = Y; y < Y + H; y++)
            {
                for(int z = Z; z < Z + D; z++)
                {
                    auto p = Position(x, y, z);
                    if(map.count(p) > 0)
                    {
                        map[p].insert(index);
                    }
                }
            }
        }
    }

    void Erase(int X, int Y, int Z, int W, int H, int D, uint index)
    {
        for(int x = X; x < X + W; x++)
        {
            for(int y = Y; y < Y + H; y++)
            {
                for(int z = Z; z < Z + D; z++)
                {
                    auto p = Position(x, y, z);
                    if(map.count(p) > 0)
                    {
                        map[p].erase(index);
                    }
                }
            }
        }
    }

    private:

        Position DirectionToPosition(Position pos, Direction dir)
        {   
            auto [x, y, z] = pos; 
            const int step = 1;
            if     (dir & UP)      x += step;
            else if(dir & DOWN)    x -= step;
            if     (dir & LEFT)    y += step;
            else if(dir & RIGHT)   y -= step;
            if     (dir & FOWARD)  z += step;
            else if(dir & BACK)    z -= step;
            return Position(x, y, z);
        }

    public:

    std::map<Direction,std::vector<T*>> GetNeighbors(const int x, const int y, const int z)
    {
        std::map<Direction, std::vector<T*>> neighbors;
        auto vec = Position(x, y, z);
        
        neighbors[UP]                    =  Get(DirectionToPosition(vec, UP                   ));                                                          
        neighbors[UP | LEFT]             =  Get(DirectionToPosition(vec, UP | LEFT            ));                                  
        neighbors[UP | LEFT | FOWARD]    =  Get(DirectionToPosition(vec, UP | LEFT | FOWARD   ));                                          
        neighbors[UP | LEFT | BACK]      =  Get(DirectionToPosition(vec, UP | LEFT | BACK     ));                                      
        neighbors[UP | RIGHT]            =  Get(DirectionToPosition(vec, UP | RIGHT           ));                                  
        neighbors[UP | RIGHT | FOWARD]   =  Get(DirectionToPosition(vec, UP | RIGHT | FOWARD  ));                                          
        neighbors[UP | RIGHT | BACK]     =  Get(DirectionToPosition(vec, UP | RIGHT | BACK    ));                                          
        neighbors[UP | FOWARD]           =  Get(DirectionToPosition(vec, UP | FOWARD          ));                                  
        neighbors[UP | BACK]             =  Get(DirectionToPosition(vec, UP | BACK            ));                                  
        neighbors[DOWN]                  =  Get(DirectionToPosition(vec, DOWN                 ));                          
        neighbors[DOWN | LEFT]           =  Get(DirectionToPosition(vec, DOWN | LEFT          ));                                  
        neighbors[DOWN | LEFT | FOWARD]  =  Get(DirectionToPosition(vec, DOWN | LEFT | FOWARD ));                                          
        neighbors[DOWN | LEFT | BACK]    =  Get(DirectionToPosition(vec, DOWN | LEFT | BACK   ));                                          
        neighbors[DOWN | RIGHT]          =  Get(DirectionToPosition(vec, DOWN | RIGHT         ));                                  
        neighbors[DOWN | RIGHT | FOWARD] =  Get(DirectionToPosition(vec, DOWN | RIGHT | FOWARD));                                              
        neighbors[DOWN | RIGHT | BACK]   =  Get(DirectionToPosition(vec, DOWN | RIGHT | BACK  ));                                          
        neighbors[DOWN | FOWARD]         =  Get(DirectionToPosition(vec, DOWN | FOWARD        ));                                      
        neighbors[DOWN | BACK]           =  Get(DirectionToPosition(vec, DOWN | BACK          ));                                  
        neighbors[LEFT]                  =  Get(DirectionToPosition(vec, LEFT                 ));                          
        neighbors[LEFT | FOWARD]         =  Get(DirectionToPosition(vec, LEFT | FOWARD        ));                                      
        neighbors[LEFT | BACK]           =  Get(DirectionToPosition(vec, LEFT | BACK          ));                                  
        neighbors[RIGHT]                 =  Get(DirectionToPosition(vec, RIGHT                ));                              
        neighbors[RIGHT | FOWARD]        =  Get(DirectionToPosition(vec, RIGHT | FOWARD       ));                                      
        neighbors[RIGHT | BACK]          =  Get(DirectionToPosition(vec, RIGHT | BACK         ));                                  
        neighbors[FOWARD]                =  Get(DirectionToPosition(vec, FOWARD               ));                              
        neighbors[BACK]                  =  Get(DirectionToPosition(vec, BACK                 ));                          
        
        return neighbors;
    }

    std::map<Direction,std::vector<T*>> GetCardinalNeighbors(const int x, const int y, const int z)
    {
        std::map<Direction, std::vector<T*>> neighbors;
        auto vec = Position(x, y, z);
                
        neighbors[UP]                    =  Get(DirectionToPosition(vec, UP                   ));                                 
        neighbors[DOWN]                  =  Get(DirectionToPosition(vec, DOWN                 ));                                
        neighbors[LEFT]                  =  Get(DirectionToPosition(vec, LEFT                 ));                                 
        neighbors[RIGHT]                 =  Get(DirectionToPosition(vec, RIGHT                ));                                  
        neighbors[FOWARD]                =  Get(DirectionToPosition(vec, FOWARD               ));                              
        neighbors[BACK]                  =  Get(DirectionToPosition(vec, BACK                 ));   

        return neighbors;
    }

};