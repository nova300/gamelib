#pragma once

#include <memory>
#include <vector>

#include "core/object.h"

class ObjectStore
{
public:
    void Add(std::shared_ptr<Object> obj);
    void Remove(std::shared_ptr<Object> obj);

    void Update(float deltaTime);
    void LateUpdate(float deltaTime);

    void ProcessNewObjects();
    
private:
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Object>> newObjects;

};