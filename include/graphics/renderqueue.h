#pragma once

#include "core/object.h"
#include <map>
#include <memory>

class RenderQueue
{
public:
    void SetPass(int pass);
    void UnsetPass();
    void Add(std::shared_ptr<Object>, int position = 0);
    void Remove(std::shared_ptr<Object>);
    void Draw();
    static void RenderAll();
private:
    std::multimap<int, std::shared_ptr<Object>> objects;
};

class RenderQueue2D
{

};

