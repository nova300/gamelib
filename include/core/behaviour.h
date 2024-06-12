#pragma once
#include <vector>

#include "physics/types.h"

class Object;

class Behaviour
{
    friend class Object;
public:
    virtual ~Behaviour() {};

    virtual void Init() {};
    virtual void Awake() {};
    virtual void Update(float deltaTime) {};
    virtual void PostUpdate(float deltaTime) {};
    virtual void Render() {};
    virtual void OnCollision(CollisionInfo info) {};

    Object* GetObject();
protected:
    Object* object = nullptr;
};