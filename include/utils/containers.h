#pragma once
#include <map>
#include <vector>
#include <raylib.h>
#include <cstddef>
#include <string>
#include <set>
#include <deque>
#include <unordered_set>

#include "utils/types.h"

template<typename T>
class PoolVector
{
private:
    struct Data
    {
        int index;
        T value;
    };

    std::vector<Data> vector;
    std::deque<int> freeIndicies;

public:
    std::vector<Data>& GetVector()
    {
        return vector;
    }
    std::map<int, T*> GetAll()
    {
        std::map<int, T*> out;

        for(Data& d : vector)
        {
            if(d.index > -1)
            {
                out[d.index] = &d.value;
            }
        }

        return out;
    }

    T* Get(unsigned int index)
    {
        if(index >= vector.size()) return nullptr;
        if(vector[index].index != index) return nullptr;
        return &vector[index].value;
    }

    unsigned int Add(T value)
    {
        /*for (int i = 0; i < vector.size() ; i++)
        {
            if(vector[i].index != i)
            {
                vector[i].index = i;
                vector[i].value = value;
                return i;
            }
        }*/

        if(!freeIndicies.empty())
        {
            int index = freeIndicies.front();
            freeIndicies.pop_front();
            if(index < vector.size())
            {
                if(vector[index].index != index)
                {
                    vector[index].index = index;
                    vector[index].value = value;
                    return index;
                }
            }
        }

        int index = vector.size();

        Data data = 
        {
            index,
            value
        };

        vector.push_back(data);

        return index;
    }

    void Remove(unsigned int index)
    {
        if(index <= vector.size()) return;
        if(vector[index].index != index) return;
        vector[index].index = -1;
        freeIndicies.push_back(index);
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
    
    //using Position = std::pair<int, int>;
private:
    std::map<long, std::unordered_set<unsigned int>> map;
    long GetPosHash(const short x, const short y)
    {
        return x<<16 + y;
    }
public:
    PoolVector<Data> storage;
private:
    std::vector<T*> Get(std::unordered_set<unsigned int> idxes)
    {
        std::vector<T*> out;
        for(unsigned int idx : idxes)
        {
            T* ptr = &storage.Get(idx)->value;
            if(ptr != nullptr) out.push_back(ptr);
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

    std::map<int, T*> GetAllActive()
    {
        std::map<int, T*> out;
        std::map<int, Data*> dat = storage.GetAll();

        for(const auto& [index, value] : dat)
        {
            if(value == nullptr) continue;
            out[index] = &value->value;
        }

        return out;
    }

    std::vector<T*> Get(int x, int y)
    {
        x = x / cellSize;
        y = y / cellSize;
        auto vec = GetPosHash(x, y);
        std::unordered_set<unsigned int> idxes;
        if (map.count(vec) > 0)
        {
            for(unsigned int idx : map[vec])
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
        std::unordered_set<unsigned int> idxes;
        for(int x = X - 1; x <= X + W + 1; x++)
        {
            for(int y = Y - 1; y <= Y + H + 1; y++)
            {
                auto p = GetPosHash(x, y);
                if (map.count(p) > 0)
                {
                    for (unsigned int idx : map[p])
                    {
                        idxes.insert(idx);
                    };
                }
            }
        }
        return Get(idxes);
    }

    std::vector<T*> Get(IntRectangle bounds)
    {
        return Get(bounds.x, bounds.y, bounds.width, bounds.height);
    }

    std::vector<T*> Get(unsigned int index)
    {
        std::unordered_set<unsigned int> indicies;
        Data *data = storage.Get(index);
        const int X = data->x / cellSize;
        const int Y = data->y / cellSize;
        const int W = data->w / cellSize;
        const int H = data->h / cellSize;
        if(W == 0) W = 1;
        if(H == 0) H = 1;
        if (data)
        {
            for (int x = X - 1; x <= X + W + 1; x++)
            {
                for (int y = Y - 1; y <= Y + H + 1; y++)
                {
                    auto p = GetPosHash(x, y);
                    if (map.count(p) > 0)
                    {
                        for (unsigned int idx : map[p])
                        {
                            indicies.insert(idx);
                        };
                    }
                }
            }
        }

        return Get(indicies);
    }

    

    void Set(unsigned int index, T value)
    {
        Data* ptr = storage.Get(index);
        if(ptr)
        {
            ptr->value = value;
        }
    }

    void Update(int x, int y, int w, int h, unsigned int index)
    {
        Data* dat = storage.Get(index);
        if(dat == nullptr) return;
        bool different = false;
        if(dat->x != x) different = true;
        if(!different && dat->y != y) different = true;
        if(!different && dat->w != w) different = true;
        if(!different && dat->h != h) different = true;
        if(!different) return;
        Erase(dat->x, dat->y, dat->w, dat->h, index);
        Fill(x, y, w, h, index);
        dat->x = x;
        dat->y = y;
        dat->w = w;
        dat->h = h;
    }

    void Update(int x, int y, int w, int h, unsigned int index, T value)
    {
        Set(index, value);
        Update(x, y, w, h, index);
    }

    void Update(IntRectangle bounds, unsigned int index)
    {
        Update(bounds.x, bounds.y, bounds.width, bounds.height, index);
    }

    void Update(IntRectangle bounds, unsigned int index, T value)
    {
        Update(bounds.x, bounds.y, bounds.width, bounds.height, index, value);
    }

    unsigned int Add(int x, int y, int w, int h, T value)
    {
        Data dat = 
        {
            x,
            y,
            w,
            h,
            value
        };
        unsigned int index = storage.Add(dat);
        Fill(x, y, w, h, index);

        return index;
    }

    unsigned int Add(IntRectangle bounds, T value)
    {
        return Add(bounds.x, bounds.y, bounds.width, bounds.height, value);
    }

    void Remove(unsigned int index)
    {
        Data *data = storage.Get(index);
        if(!data) return;
        Erase(data->x, data->y, data->w, data->h, index);
        storage.Remove(index);
    }

    void Fill(int X, int Y, int W, int H, unsigned int index)
    {
        X = X / cellSize;
        Y = Y / cellSize;
        W = W / cellSize;
        H = H / cellSize;
        if(W == 0) W = 1;
        if(H == 0) H = 1;
        for(int x = X; x < X + W; x++)
        {
            for(int y = Y; y < Y + H; y++)
            {
                auto p = GetPosHash(x, y);
                map[p].insert(index);
            }
        }
    }

    void Erase(int X, int Y, int W, int H, unsigned int index)
    {
        X = X / cellSize;
        Y = Y / cellSize;
        W = W / cellSize;
        H = H / cellSize;
        if(W == 0) W = 1;
        if(H == 0) H = 1;
        for(int x = X; x < X + W; x++)
        {
            for(int y = Y; y < Y + H; y++)
            {
                auto p = GetPosHash(x, y);
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
    std::map<Position, std::set<unsigned int>> map;
    PoolVector<Data> storage;

    std::vector<T*> Get(std::set<unsigned int> idxes)
    {
        std::vector<T*> out;
        for(unsigned int idx : idxes)
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
        std::set<unsigned int> idxes;
        if (map.count(vec) > 0)
        {
            for(unsigned int idx : map[vec])
            {
                idxes.insert(idx);
            }
        }
        return Get(idxes);
    }

    std::vector<T*> Get(int X, int Y, int Z, int W, int H, int D)
    {
        std::set<unsigned int> idxes;
        for(int x = X; x < X + W; x++)
        {
            for(int y = Y; y < Y + H; y++)
            {
                for(int z = Z; z < Z + D; z++)
                {
                    auto p = Position(x, y, z);
                    if (map.count(p) > 0)
                    {
                        for (unsigned int idx : map[p])
                        {
                            idxes.insert(idx);
                        };
                    }
                }
            }
        }
        return Get(idxes);
    }

    std::vector<T*> Get(unsigned int index)
    {
        std::set<unsigned int> indicies;
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
                            for (unsigned int idx : map[p])
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

    

    void Set(unsigned int index, T value)
    {
        Data* ptr = storage.Get(index);
        if(ptr)
        {
            ptr->value = value;
        }
    }

    void Update(int x, int y, int z, int w, int h, int d, unsigned int index)
    {
        Data* dat = storage.Get(index);
        if(dat == nullptr) return;
        Erase(dat->x, dat->y, dat->z, dat->w, dat->h, dat->d, index);
        Fill(x, y, z, w, h, d, index);
    }

    void Update(int x, int y, int z, int w, int h, int d, unsigned int index, T value)
    {
        Set(index, value);
        Update(x, y, z, w, h, d, index);
    }

    unsigned int Add(int x, int y, int z, int w, int h, int d, T value)
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
        unsigned int index = storage.Add(value);
        Fill(x, y, z, w, h, d, index);

        return index;
    }

    void Remove(unsigned int index)
    {
        Data *data = storage.Get(index);
        if(!data) return;
        Erase(data->x, data->y, data->z, data->w, data->h, data->d, index);
        storage.Remove(data);
    }

    void Fill(int X, int Y, int Z, int W, int H, int D, unsigned int index)
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

    void Erase(int X, int Y, int Z, int W, int H, int D, unsigned int index)
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