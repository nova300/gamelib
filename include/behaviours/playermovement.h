#pragma once

#include "core/behaviour.h"
#include <raylib.h>
#include <memory>
#include "graphics/animatedsprite.h"

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
    ~PlayerMovement() {};

    void SetMovementSpeed(float moveSpeed);

    void Update(float deltaTime) override;
    void Init() override;

private:
    float moveSpeed = 100.0f;
    Direction dir = DOWN;
    std::weak_ptr<AnimatedSprite> spritePtr;
};