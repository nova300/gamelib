#include "graphics/animatedsprite.h"
#include "core/object.h"

void AnimatedSprite::Update(float deltaTime)
{
    if(animations.empty()) return;
    
    if(animations.count(currentAnimation) == 0) return;

    auto& currentVec = animations.at(currentAnimation);
    if(currentVec.empty()) return;

    auto& frame = currentVec[currentFrame];

    if(timer < frame.time)
    {
        timer += deltaTime;
    }
    else
    {
        timer = 0.0f;
        currentFrame++;
        if (currentFrame >= currentVec.size()) // out of frames, play next animation or loop if unlinked
        {
            currentFrame = 0;
            if (animationLinks.count(currentAnimation) == 1)
            {
                int next = animationLinks[currentAnimation];
                if (animations.count(next) == 1)
                {
                    if (!animations.at(next).empty())
                    {
                        currentAnimation = next;
                    }
                }
            }
        }
    }
}

void AnimatedSprite::SetFlip(bool val)
{
    if(val == flip) return;
    flip = val;
}

void AnimatedSprite::Render()
{
    if(animations.empty()) return;
    if(animations.count(currentAnimation) == 0) return;

    auto& currentVec = animations.at(currentAnimation);

    if(currentVec.empty()) return;
    if(currentFrame < currentVec.size())
    {
        auto& frame = currentVec[currentFrame];

        auto pos = GetObject()->position;

        Rectangle src = frame.src;
        Rectangle dst = Rectangle{pos.x, pos.y, (float)frame.height * pos.scale.x, (float)frame.width * pos.scale.y};
        if(flip) src = Rectangle{src.x, src.y, -src.width, src.height};
        DrawTexturePro(frame.tex->Texture(), src, dst, Vector2{0.0f, 0.0f}, pos.rotation.z, frame.color);
    }
    
}

void AnimatedSprite::PushFrame(int animationID, SpriteFrame frame)
{
    animations[animationID].push_back(frame);
}

void AnimatedSprite::SetAnimationLink(int animationID, int linkedAnimationID)
{
    animationLinks[animationID] = linkedAnimationID;
}
    
void AnimatedSprite::Play(int animationID)
{
    if(animationID == currentAnimation) return;
    if(animations.empty()) return;
    if(animations.count(animationID) == 0) return;

    timer = 0.0f;
    currentFrame = 0;
    currentAnimation = animationID;
}