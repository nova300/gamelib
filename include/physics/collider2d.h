#pragma once

#include <raylib.h>
#include <raymath.h>

#include <vector>
#include <memory>
#include <map>

#include "core/behaviour.h"
#include "core/object.h"


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
    bool CheckStep(Vector2 step);
    bool operator==(const Collider& other) const
    { 
        if(this->type != other.type) return false;
        if(this->data.rect.x != other.data.rect.x) return false;
        if(this->data.rect.y != other.data.rect.y) return false;
        if(this->data.rect.width != other.data.rect.width) return false;
        if(this->data.rect.height != other.data.rect.height) return false;
        return true;
    }
};



// like renderqueue, but colliders
class ColliderSet
{
public:
    void Update();


private:
    Map2D<Collider> collisionMap;
};


};
