#pragma once

#include <memory>
#include <vector>

#include "core/object.h"

class ObjectStore
{
public:
    void AddObject(Object* obj);
    void AddObject(std::shared_ptr<Object> obj);
    void RemoveObject(Object* obj);

    void UpdateObjects(float deltaTime);
    void PostUpdateObjects(float deltaTime);

    void ProcessNewObjects();
    
private:
    std::vector<Object*> objects;
    std::vector<Object*> newObjects;
    std::vector<std::weak_ptr<Object>> objects_ptr;
    std::vector<std::shared_ptr<Object>> newObjects_ptr;

};