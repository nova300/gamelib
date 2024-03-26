#pragma once

#include "core/behaviour.h"
#include <raylib.h>

class PlayerMovement : public Behaviour
{
public:
    PlayerMovement(Object* obj);

    void SetMovementSpeed(float moveSpeed);

    void Update(float deltaTime) override;

private:
    float moveSpeed;
};