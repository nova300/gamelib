#include "behaviours/movement.h"
#include "core/object.h"
#include "stdio.h"

void Movement::Init()
{
    collider = object->GetBehaviour<Collider>();
    if (!collider.expired())
    {
        printf("MOVEMENT BEHAVIOUR: could not find collider behaviour!\n");
    }
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

void Movement::SetCollider(std::weak_ptr<Collider> COLLIDER)
{
    collider = COLLIDER;
}

void Movement::Update(float deltaTime)
{

    Vector3 moveStep = Vector3Scale(velocity, moveSpeed * deltaTime);

    auto col = collider.lock();
    if(col)
    {
        Vector3Scale(moveStep, col->CheckStep(moveStep));
    }

    object->position.local.Translate(moveStep);
}
