#pragma once

#include <raylib.h>
#include <raymath.h>

#include <vector>
#include <memory>
#include <map>

#include "core/behaviour.h"
#include "core/object.h"

#define MAX_COLLIDERS 64;

class ColliderSet;

struct CollisionInfo
{
    Object *other = NULL;
    Vector2 position = Vector2Zero();
    Vector2 pushout = Vector2Zero();
    Vector2 normal = Vector2Zero();
};

enum CollisionShape
{
    COL_UNDEFINED,
    COL_POINT,
    COL_BOX,
    COL_SPRITE,
    COL_CIRCLE
};

struct ColliderShapeData
{
    Object* object = NULL;
    std::weak_ptr<Collider> owner;
    CollisionShape type = COL_UNDEFINED;
    Vector2 offset = Vector2Zero();
    struct Circle
    {
        float radius;
    };
    struct Box
    {
        float width;
        float height;
    };
    union Data
    {
        Box box;
        Circle circle;
    };
    Data data;
};

/*enum CollisionFlags
{
    FLG_SOLID,
    FLG_HITBOX
};

struct ColliderShape
{
    Vector2 position;
    Vector2 offset;
    std::weak_ptr<Behaviour> owner;
    bool UpdatePosition();
    virtual bool Check(ColliderShape *collider) = 0;
};

struct PointCollider : ColliderShape
{
    bool Check(ColliderShape *collider) override;
};

struct BoxCollider : ColliderShape
{
    Vector2 size;
    bool Check(ColliderShape *collider) override;
};

struct CircleCollider : ColliderShape
{
    float radius;
    bool Check(ColliderShape *collider) override;
};

enum CollisionChannels
{
    FLG_SOLID,
    FLG_HITBOX
};

class CollisionChannel
{
public:
    std::vector<PointCollider> points;
    std::vector<BoxCollider> boxes;
    std::vector<CircleCollider> circles;
};*/

class Collider : public Behaviour
{
    friend class ColliderSet;
public:
    void SetBox(Rectangle bounds);
    void SetSprite();
    void SetCircle(Vector2 pos, float radius);
    void SetPoint(Vector2 offset = Vector2Zero());

protected:
    Rectangle Box();
    Rectangle Sprite();
    float Radius();
    Vector2 Point();

    bool Overlap(Collider *other);
    CollisionInfo Info(Collider *other);

private:
    CollisionShape type = COL_UNDEFINED;
    float offsetX;
    float offsetX;
    float width;
    float height;

};



class ColliderSet
{
public:
    void AddCollider(Object* obj);
    void RemoveCollider(Object* obj);

    void UpdateColliders();

private:
    std::vector<std::weak_ptr<Collider>> colliders;

};
