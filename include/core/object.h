#pragma once

#include "core/behaviour.h"
#include "core/program.h"
#include "core/position.h"

class Program;

#include <memory>

class Object
{
public:
    //overridable update and render methods
    virtual void Awake() {};
    virtual void Init() {};
    virtual void Update(float deltaTime) {};
    virtual void LateUpdate(float deltaTime) {};
    virtual void Render() {};

    void AwakeBehaviours();
    void InitBehaviours();
    void UpdateBehaviours(float deltaTime);
    void LateUpdateBehaviours(float deltaTime);
    void RenderBehaviours();

    Position position;

    Program* GetProgram();

    //active / visible getters and setters
    bool Active();
    bool Visible();
    void Active(bool value);
    void Visible(bool value);

    template<typename T>
    std::shared_ptr<T> AddBehaviour();
    
    template<typename T> 
    std::shared_ptr<T> GetBehaviour();

    template<class T>
    void RemoveBehaviour();

protected:
    std::vector<std::shared_ptr<Behaviour>> behaviours;
    bool active = true;
    bool visible = true;
};


template <typename T>
std::shared_ptr<T> Object::AddBehaviour()
{
    static_assert(std::is_base_of<Behaviour, T>::value, "T is not a component");
    for(auto& b : behaviours)
    {
        if(std::dynamic_pointer_cast<T>(b))
        {
            return std::dynamic_pointer_cast<T>(b);
        }
    }

    std::shared_ptr<T> newBehaviour = std::make_shared<T>(this);
    newBehaviour->object = this;
    behaviours.push_back(newBehaviour);

    return newBehaviour;
}

template <typename T>
std::shared_ptr<T> Object::GetBehaviour()
{
    for(auto& b : behaviours)
    {
        if(std::dynamic_pointer_cast<T>(b))
        {
            return std::dynamic_pointer_cast<T>(b);
        }
    }
    return nullptr;
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