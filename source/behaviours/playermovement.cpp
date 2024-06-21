#include "behaviours/playermovement.h"
#include "core/object.h"
#include "core/input.h"
#include "graphics/animatedsprite.h"

void PlayerMovement::Init()
{
    spritePtr = GetObject()->GetBehaviour<AnimatedSprite>();
}

void PlayerMovement::SetMovementSpeed(float movespeed)
{
    this->moveSpeed = movespeed;
}

void PlayerMovement::Update(float deltaTime)
{
    
    auto turn = getTurnInput();
    auto pitch = getPitchInput();

    auto sprite = spritePtr.lock();

    if (sprite.get() != nullptr)
    {
        if (abs(turn) > 0.1f || abs(pitch) > 0.1f)
        {
            if (turn > 0)
                dir = RIGHT;
            else if (turn < 0)
                dir = LEFT;
            else if (pitch > 0)
                dir = DOWN;
            else if (pitch < 0)
                dir = UP;

            switch (dir)
            {
            case UP:
                sprite->Play(PlayerAnimations::RUN_UP);
                break;
            
            case DOWN:
                sprite->Play(PlayerAnimations::RUN_DOWN);
                break;
            
            case LEFT:
                sprite->Play(PlayerAnimations::RUN_SIDE);
                sprite->SetFlip(true);
                break;
            
            case RIGHT:
                sprite->Play(PlayerAnimations::RUN_SIDE);
                sprite->SetFlip(false);
                break;
            }
            
        }
        else
        {
            switch (dir)
            {
            case UP:
                sprite->Play(PlayerAnimations::UP);
                break;
            
            case DOWN:
                sprite->Play(PlayerAnimations::DOWN);
                break;
            
            case LEFT:
                sprite->Play(PlayerAnimations::SIDE);
                sprite->SetFlip(true);
                break;
            
            case RIGHT:
                sprite->Play(PlayerAnimations::SIDE);
                sprite->SetFlip(false);
                break;
            }
        }
    }

    turn *= moveSpeed * deltaTime;
    pitch *= moveSpeed * deltaTime;

    GetObject()->position.local.Translate(turn, pitch);


    
}