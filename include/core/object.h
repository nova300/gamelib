#pragma once

#include "core/behaviour.h"
#include "core/position.h"

class Program;

#include <memory>

class Object
{
friend class Program;
friend class RenderQueue;
friend class ProgramStack;
public:
    //overridable update and render methods
    virtual ~Object() {};
    virtual void Init() {};
    virtual void Update(float deltaTime) {};
    virtual void PostUpdate(float deltaTime) {};
    //virtual void Render() {};

    //common data
    Position position;

    //node tree
    template<typename T>
    std::weak_ptr<T> AddChild();

    std::weak_ptr<Object> AddChild()
    {
        return AddChild<Object>();
    }

    void AddChild(std::shared_ptr<Object> obj);
    void RemoveChild(std::shared_ptr<Object> obj);

    template<typename T>
    std::weak_ptr<T> AddBehaviour();
    
    template<typename T> 
    std::weak_ptr<T> GetBehaviour();

    template<class T>
    void RemoveBehaviour();

    template<typename T> 
    std::vector<T*> GetAllOfType(bool hierarchicalSearch = false, bool includePreInitObjects = false);
    
protected:
    virtual void UpdateInternal(float deltaTime);
    virtual void PostUpdateInternal(float deltaTime);
    //virtual void RenderInternal();
    void UpdateWorldPos(void);

    //behaviour data
    std::vector<std::shared_ptr<Behaviour>> behaviours;
    std::vector<std::shared_ptr<Behaviour>> newbehaviours;

    //node tree data
    std::vector<std::shared_ptr<Object>> childObjects;
    std::vector<std::shared_ptr<Object>> newchildObjects;
    Object* parent = nullptr;
    Program* program = nullptr;
    int level = 0;
    bool sleep = false;

public:
    Program* GetProgram()
    {
        return program;
    }
};


template <typename T>
std::weak_ptr<T> Object::AddChild()
{
    static_assert(std::is_base_of<Object, T>::value, "T is not a object");

    std::shared_ptr<T> newObject = std::make_shared<T>();
    newObject->program = program;
    newObject->parent = this;
    newchildObjects.push_back(newObject);

    return newObject;
}


template <typename T>
std::weak_ptr<T> Object::AddBehaviour()
{
    static_assert(std::is_base_of<Behaviour, T>::value, "T is not a component");
    for(auto& b : behaviours)
    {
        auto ptr = std::dynamic_pointer_cast<T>(b);
        if(ptr)
        {
            return ptr;
        }
    }

    std::shared_ptr<T> newBehaviour = std::make_shared<T>();
    newBehaviour->object = this;
    newbehaviours.push_back(newBehaviour);

    return newBehaviour;
}

template <typename T>
std::weak_ptr<T> Object::GetBehaviour()
{
    for(auto& b : behaviours)
    {
        auto ptr = std::dynamic_pointer_cast<T>(b);
        if(ptr)
        {
            return ptr;
        }
    }
    for(auto& b : newbehaviours)
    {
        auto ptr = std::dynamic_pointer_cast<T>(b);
        if(ptr)
        {
            return ptr;
        }
    }
    return {}; //looks weird, returns empty weak_ptr
}

template <typename T>
std::vector<T*> Object::GetAllOfType(bool hierarchicalSearch, bool includePreInitObjects)
{
    std::vector<T*> objs;

    T* self = dynamic_cast<T*>(this);
    if(self)
    {
        objs.push_back(self);
    }

    for(auto& b : behaviours)
    {
        auto ptr = std::dynamic_pointer_cast<T>(b);
        if(ptr)
        {
            objs.push_back(ptr.get());
        }
    }
    if(includePreInitObjects)
    {
        for (auto &b : newbehaviours)
        {
            auto ptr = std::dynamic_pointer_cast<T>(b);
            if (ptr)
            {
                objs.push_back(ptr.get());
            }
        }
    }

    if(hierarchicalSearch)
    {
        for(auto &c : childObjects)
        {
            if(c->sleep = true) continue;
            auto cobjs = c->GetAllOfType<T>(hierarchicalSearch, includePreInitObjects);
            objs.insert(objs.end(), cobjs.begin(), cobjs.end());
        }
    }

    return objs;
}

template <typename T>
void Object::RemoveBehaviour()
{
    for(int i = 0; i < behaviours.size(); i++)
    {
        if (behaviours[i] == std::dynamic_pointer_cast<T>(behaviours[i]))
        {
            behaviours.erase(behaviours.begin() + i);
            return;
        }
    }
    return;
}