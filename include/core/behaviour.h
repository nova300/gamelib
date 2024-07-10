#pragma once
#include <vector>

class Object;

class Behaviour
{
    friend class Object;
public:
    virtual ~Behaviour() {};

    virtual void Init() {};
    virtual void Update(float deltaTime) {};
    virtual void PostUpdate(float deltaTime) {};
    //virtual void Render() {};

    Object* GetObject();
protected:
    Object* object = nullptr;
};