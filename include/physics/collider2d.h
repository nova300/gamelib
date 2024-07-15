#pragma once

#include <raylib.h>
#include <raymath.h>

#include <vector>
#include <memory>
#include <map>

#include "core/behaviour.h"
#include "core/object.h"
#include "utils/containers.h"


namespace Collider2D
{
struct Collider;
class ColliderSet;
class IHasCollider;

enum class ColliderType
{
    UNDEFINED,
    RECTANGLE,
    CIRCLE,
    POINT
};

struct CollisionInfo
{
    IHasCollider *other = nullptr;
    Vector2 position = Vector2Zero();
    Vector2 pushout = Vector2Zero();
    Vector2 normal = Vector2Zero();

    template<typename T>
    T* GetOther()
    {
        return dynamic_cast<T>(other);
    }
};

struct Collider
{
    IHasCollider* owner = nullptr;
    ColliderSet* set = nullptr;
    ColliderType type = ColliderType::UNDEFINED;
    union Data
    {
        Vector2 point;
        Rectangle rect;
        struct Circle
        {
            float x;
            float y;
            float radius;
        }circle;   
    }data;
    inline Rectangle Rect()
    {
        return data.rect;
    }
    inline float Radius()
    {
        return data.circle.radius;
    }
    inline Vector2 Point()
    {
        return data.point;
    }

    bool CheckCollision(Collider* other, CollisionInfo* details = nullptr);
    
    bool operator==(const Collider& other) const
    { 
        if(this->type != other.type) return false;
        if(this->data.rect.x != other.data.rect.x) return false;
        if(this->data.rect.y != other.data.rect.y) return false;
        if(this->data.rect.width != other.data.rect.width) return false;
        if(this->data.rect.height != other.data.rect.height) return false;
        return true;
    }

    template<typename T>
    T* GetOwner()
    {
        return dynamic_cast<T>(owner);
    }
};



// like renderqueue, but colliders
class ColliderSet
{
public:
    void Update();
    float CheckStep(int index, Vector2 step);

private:
    Map2D<Collider> collisionMap;
};


};
