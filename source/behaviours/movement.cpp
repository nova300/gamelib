#include "behaviours/movement.h"
#include "core/object.h"
#include "stdio.h"

void Movement::Init()
{

}

void Movement::SetMovementSpeed(float MOVESPEED)
{
    moveSpeed = MOVESPEED;
}

void Movement::SetVelocity(Vector3 VELOCITY)
{
    velocity = VELOCITY;
}

void Movement::SetVelocity(Vector2 VELOCITY)
{
    velocity.x = VELOCITY.x;
    velocity.y = VELOCITY.y;
}

void Movement::SetCollider(Collider2D::Collider COLLIDER)
{
    collider = COLLIDER;
}

void Movement::Update(float deltaTime)
{

    Vector3 moveStep = Vector3Scale(velocity, moveSpeed * deltaTime);

    /*auto col = collider.lock();
    if(col)
    {
        Vector3Scale(moveStep, col->CheckStep(moveStep));
    }*/

    object->position.local.Translate(moveStep);
}

Collider2D::Collider Movement::GetCollider(Collider2D::ColliderSet* set)
{
    collider.owner = this;
    collider.data.point = GetObject()->position.world.Vec2();
    return collider;
}

void OnCollision(const Collider2D::CollisionInfo& details)
{

}
