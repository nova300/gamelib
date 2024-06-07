#include "behaviours/movement.h"
#include "core/object.h"
#include "stdio.h"

Movement::Movement(Object *obj) : Behaviour(obj)
{
    collider = obj->GetBehaviour<Collider>();
    if (collider == nullptr)
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

void Movement::SetCollider(std::shared_ptr<Collider> COLLIDER)
{
    collider = COLLIDER;
}

void Movement::Update(float deltaTime)
{

    Vector3 moveStep = Vector3Scale(velocity, moveSpeed * deltaTime);

    if(collider)
    {
        Vector3Scale(moveStep, collider->CheckStep(moveStep));
    }

    object->position.Translate(moveStep);
}
