#pragma once

#include <memory>
#include <vector>

#include "core/object.h"

class ObjectStore
{
public:
    void AddObject(Object* obj);
    void RemoveObject(Object* obj);

    void UpdateObjects(float deltaTime);
    void PostUpdateObjects(float deltaTime);

    void ProcessNewObjects();
    
private:
    std::vector<Object*> objects;
    std::vector<Object*> newObjects;

};