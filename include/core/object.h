#pragma once

#include "core/behaviour.h"
#include "core/position.h"
#include "physics/types.h"

class Program;

#include <memory>

class Object
{
public:
    //overridable update and render methods
    virtual ~Object() {};
    virtual void Awake() {};
    virtual void Init() {};
    virtual void Update(float deltaTime) {};
    virtual void PostUpdate(float deltaTime) {};
    virtual void Render() {};
    virtual void OnCollision(CollisionInfo info) {};

    void AwakeBehaviours();
    void InitBehaviours();
    void UpdateBehaviours(float deltaTime);
    void PostUpdateBehaviours(float deltaTime);
    void RenderBehaviours();
    void OnCollisionBehaviours(CollisionInfo info);

    std::vector<CollisionShape> GetColliders();

    //std::vector<Rectangle> GetCollisionRects();
    //std::vector<Vector3> GetCollisionCircles();
    //std::vector<Vector2> GetCollisionPoints();

    Position position;

    //active / visible getters and setters
    bool Active();
    bool Visible();
    void Active(bool value);
    void Visible(bool value);

    template<typename T>
    std::weak_ptr<T> AddBehaviour();
    
    template<typename T> 
    std::weak_ptr<T> GetBehaviour();

    template<class T>
    void RemoveBehaviour();

protected:
    std::vector<std::shared_ptr<Behaviour>> behaviours;
    bool active = true;
    bool visible = true;
};


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
    behaviours.push_back(newBehaviour);
    newBehaviour->Init();

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
    return {}; //looks weird, returns empty weak_ptr
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