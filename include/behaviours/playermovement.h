#pragma once

#include "core/behaviour.h"
#include <raylib.h>

enum PlayerAnimations
{
    DOWN,
    UP,
    SIDE,
    RUN_DOWN,
    RUN_UP,
    RUN_SIDE
};



class PlayerMovement : public Behaviour
{
public:
    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    PlayerMovement(Object* obj);

    void SetMovementSpeed(float moveSpeed);

    void Update(float deltaTime) override;

private:
    float moveSpeed;
    Direction dir = DOWN;
};