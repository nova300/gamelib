#include "physics/collider.h"
#include <stdio.h>
#include "utils.h"


bool Collider::Overlap(Collider *other)
{
    switch (type)
    {
    case COL_BOX:
        switch (other->type)
        {
        case COL_BOX:
            return CheckCollisionRecs(Box(), other->Box());
            break;

        case COL_SPRITE:
            return CheckCollisionRecs(Box(), other->Sprite());
            break;

        case COL_CIRCLE:
            return CheckCollisionCircleRec(other->Point(), other->Radius(), Box());
            break;

        case COL_POINT:
            return CheckCollisionPointRec(other->Point(), Box());
            break;
        }
        break;

    case COL_SPRITE:
        switch (other->type)
        {
        case COL_BOX:
            return CheckCollisionRecs(Sprite(), other->Box());
            break;

        case COL_SPRITE:
            return CheckCollisionRecs(Sprite(), other->Sprite());
            break;

        case COL_CIRCLE:
            return CheckCollisionCircleRec(other->Point(), other->Radius(), Sprite());
            break;

        case COL_POINT:
            return CheckCollisionPointRec(other->Point(), Sprite());
            break;
        }
        break;
    
    case COL_CIRCLE:
        switch (other->type)
        {
        case COL_BOX:
            return CheckCollisionCircleRec(Point(), Radius(), other->Box());
            break;

        case COL_SPRITE:
            return CheckCollisionCircleRec(Point(), Radius(), other->Sprite());
            break;

        case COL_CIRCLE:
            return CheckCollisionCircles(Point(), Radius(), other->Point(), other->Radius());
            break;

        case COL_POINT:
            return CheckCollisionPointCircle(other->Point(), Point(), Radius());
            break;
        }
        break;

    case COL_POINT:
        switch (other->type)
        {
        case COL_BOX:
            return CheckCollisionPointRec(Point(), other->Box());
            break;

        case COL_SPRITE:
            return CheckCollisionPointRec(Point(), other->Sprite());
            break;

        case COL_CIRCLE:
            return CheckCollisionPointCircle(Point(), other->Point(), other->Radius());
            break;

        case COL_POINT:
            return (bool)Vector2Equals(Point(), other->Point());
        }
        break;

    }

    return false;

}

static void GenInfoBoxBox(CollisionInfo &info, Rectangle near, Rectangle far)
{
    float dx = far.x - near.x;
    float px = ((far.width / 2) + (near.width / 2)) - abs(dx);
    if(px <= 0)
    {
        printf("PHYSICS: tried to get info for non intersecting boxbox: X AXIS ERROR\n");
        return;
    }

    float dy = far.y - near.y;
    float py = ((far.height / 2) + (near.height / 2)) - abs(dy);
    if(py <= 0)
    {
        printf("PHYSICS: tried to get info for non intersecting boxbox: Y AXIS ERROR\n");
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


CollisionInfo Collider::Info(Collider *other)
{
    CollisionInfo info = {0};
    info.other = other->GetObject();
    info.normal = Vector2Zero();
    info.pushout = Vector2Zero();
    
    switch (type)
    {
    case COL_BOX:
        switch (other->type)
        {
        case COL_BOX:
            GenInfoBoxBox(info, Box(), other->Box());
            break;

        case COL_SPRITE:
            GenInfoBoxBox(info, Box(), other->Sprite());
            break;

        case COL_CIRCLE:
            return CheckCollisionCircleRec(other->Point(), other->Radius(), Box());
            break;

        case COL_POINT:
            return CheckCollisionPointRec(other->Point(), Box());
            break;
        }
        break;

    case COL_SPRITE:
        switch (other->type)
        {
        case COL_BOX:
            return CheckCollisionRecs(Sprite(), other->Box());
            break;

        case COL_SPRITE:
            return CheckCollisionRecs(Sprite(), other->Sprite());
            break;

        case COL_CIRCLE:
            return CheckCollisionCircleRec(other->Point(), other->Radius(), Sprite());
            break;

        case COL_POINT:
            return CheckCollisionPointRec(other->Point(), Sprite());
            break;
        }
        break;
    
    case COL_CIRCLE:
        switch (other->type)
        {
        case COL_BOX:
            return CheckCollisionCircleRec(Point(), Radius(), other->Box());
            break;

        case COL_SPRITE:
            return CheckCollisionCircleRec(Point(), Radius(), other->Sprite());
            break;

        case COL_CIRCLE:
            return CheckCollisionCircles(Point(), Radius(), other->Point(), other->Radius());
            break;

        case COL_POINT:
            return CheckCollisionPointCircle(other->Point(), Point(), Radius());
            break;
        }
        break;

    case COL_POINT:
        switch (other->type)
        {
        case COL_BOX:
            return CheckCollisionPointRec(Point(), other->Box());
            break;

        case COL_SPRITE:
            return CheckCollisionPointRec(Point(), other->Sprite());
            break;

        case COL_CIRCLE:
            return CheckCollisionPointCircle(Point(), other->Point(), other->Radius());
            break;

        case COL_POINT:
            return (bool)Vector2Equals(Point(), other->Point());
        }
        break;

    }

    return false;

}

