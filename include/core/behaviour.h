#pragma once
#include <vector>

class Object;

class Behaviour
{
    friend class Object;
public:
    Behaviour(Object* OBJ) : object(OBJ) {};

    virtual void Awake() {};
    virtual void Init() {};
    virtual void Update(float deltaTime) {};
    virtual void LateUpdate(float deltaTime) {};
    virtual void Render() {};

    Object* GetObject();
protected:
    Object* object = NULL;
};