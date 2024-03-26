#include "behaviours/playermovement.h"
#include "core/object.h"
#include "core/input.h"

PlayerMovement::PlayerMovement(Object* obj) : Behaviour(obj), moveSpeed(100) {}

void PlayerMovement::SetMovementSpeed(float movespeed)
{
    this->moveSpeed = movespeed;
}

void PlayerMovement::Update(float deltaTime)
{
    auto turn = getTurnInput();
    auto pitch = getPitchInput();

    turn *= moveSpeed * deltaTime;
    pitch *= moveSpeed * deltaTime;

    GetObject()->position.Translate(pitch, turn);
    
}