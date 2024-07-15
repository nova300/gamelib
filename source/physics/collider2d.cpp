#include "physics/collider2d.h"
#include <stdio.h>
#include "interfaces.h"
#include "utils/utils.h"
#include "utils/containers.h"

inline bool Collider2D::IHasCollider::CheckColliderDirty(const Collider2D::Collider& other)
{
    if(other == GetCollider()) return false;
    return true;
}

void Collider2D::ColliderSet::Update()
{
    //query objects and update diffs
    //run throu all in map, where there is > 1 colliders run checks, record collider pairs run so we dont do them again
}

bool Collider2D::Collider::CheckCollision(Collider* other, Collider2D::CollisionInfo* details)
{
    switch (type)
    {
    case Collider2D::ColliderType::RECTANGLE:
        switch (other->type)
        {
        case Collider2D::ColliderType::RECTANGLE:
            return CheckCollisionRecs(Rect(), other->Rect());
            break;

        case Collider2D::ColliderType::CIRCLE:
            return CheckCollisionCircleRec(other->Point(), other->Radius(), Rect());
            break;

        case Collider2D::ColliderType::POINT:
            return CheckCollisionPointRec(other->Point(), Rect());
            break;
        }
        break;
    
    case Collider2D::ColliderType::CIRCLE:
        switch (other->type)
        {
        case Collider2D::ColliderType::RECTANGLE:
            return CheckCollisionCircleRec(Point(), Radius(), other->Rect());
            break;

        case Collider2D::ColliderType::CIRCLE:
            return CheckCollisionCircles(Point(), Radius(), other->Point(), other->Radius());
            break;

        case Collider2D::ColliderType::POINT:
            return CheckCollisionPointCircle(other->Point(), Point(), Radius());
            break;
        }
        break;

    case Collider2D::ColliderType::POINT:
        switch (other->type)
        {
        case Collider2D::ColliderType::RECTANGLE:
            return CheckCollisionPointRec(Point(), other->Rect());
            break;

        case Collider2D::ColliderType::CIRCLE:
            return CheckCollisionPointCircle(Point(), other->Point(), other->Radius());
            break;

        case Collider2D::ColliderType::POINT:
            return (bool)Vector2Equals(Point(), other->Point());
        }
        break;

    }

    return false;

}

static void GenInfoRect(Collider2D::CollisionInfo &info, Rectangle near, Rectangle far)
{
    float dx = far.x - near.x;
    float px = ((far.width / 2) + (near.width / 2)) - abs(dx);
    if(px <= 0)
    {
        printf("PHYSICS: tried to get info for non intersecting Rect: X AXIS ERROR\n");
        return;
    }

    float dy = far.y - near.y;
    float py = ((far.height / 2) + (near.height / 2)) - abs(dy);
    if(py <= 0)
    {
        printf("PHYSICS: tried to get info for non intersecting Rect: Y AXIS ERROR\n");
        return;
    }

    if(px < py)
    {
        float sx = sign(dx);
        info.pushout.x = px * sx;
        info.normal.x = sx;
        info.position.x = near.x + ((near.width / 2) * sx);
        info.position.y = far.y;
    }
    else
    {
        float sy = sign(dx);
        info.pushout.y = py * sy;
        info.normal.y = sy;
        info.position.x = far.x;
        info.position.y = near.y + ((near.height / 2) * sy);
    }
}


/*Collider2D::CollisionInfo Collider2D::Collider::Info(Collider2D::Collider *other)
{
    Collider2D::CollisionInfo info = {0};
    info.other = other->;
    info.normal = Vector2Zero();
    info.pushout = Vector2Zero();
    
    switch (type)
    {
    case Collider2D::ColliderType::RECTANGLE:
        switch (other->type)
        {
        case Collider2D::ColliderType::RECTANGLE:
            GenInfoRect(info, Rect(), other->Rect());
            break;

        case Collider2D::ColliderType::CIRCLE:
            //return CheckCollisionCircleRec(other->Point(), other->Radius(), Rect());
            break;

        case Collider2D::ColliderType::POINT:
            //return CheckCollisionPointRec(other->Point(), Rect());
            break;
        }
        break;
    
    case Collider2D::ColliderType::CIRCLE:
        switch (other->type)
        {
        case Collider2D::ColliderType::RECTANGLE:
            //return CheckCollisionCircleRec(Point(), Radius(), other->Rect());
            break;

        case Collider2D::ColliderType::CIRCLE:
            //return CheckCollisionCircles(Point(), Radius(), other->Point(), other->Radius());
            break;

        case Collider2D::ColliderType::POINT:
            //return CheckCollisionPointCircle(other->Point(), Point(), Radius());
            break;
        }
        break;

    case Collider2D::ColliderType::POINT:
        switch (other->type)
        {
        case Collider2D::ColliderType::RECTANGLE:
            //return CheckCollisionPointRec(Point(), other->Rect());
            break;

        case Collider2D::ColliderType::CIRCLE:
            //return CheckCollisionPointCircle(Point(), other->Point(), other->Radius());
            break;

        case Collider2D::ColliderType::POINT:
            //return (bool)Vector2Equals(Point(), other->Point());
            break;
        }
        break;

    }

    return info;

}*/

