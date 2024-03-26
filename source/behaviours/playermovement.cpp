#include "behaviours/playermovement.h"
#include "core/object.h"

PlayerMovement::PlayerMovement(Object* obj) : Behaviour(obj), moveSpeed(100) {}

void PlayerMovement::SetMovementSpeed(float movespeed)
{
    this->moveSpeed = movespeed;
}

void PlayerMovement::Update(float deltaTime)
{
    float xMove = 0.0f;

    
}