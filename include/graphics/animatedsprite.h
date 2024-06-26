#pragma once

#include "core/behaviour.h"
#include "graphics/sprite.h"
#include "core/textureCache.h"
#include <raylib.h>
#include <string>
#include <vector>
#include <map>

struct SpriteFrame
{
    float time;
    float width;
    float height;
    Color color = WHITE;
    Rectangle src;
    std::shared_ptr<CTexture> tex;
};

class AnimatedSprite : public Behaviour, public GeoObject
{
public:
    ~AnimatedSprite() {};
    void Update(float deltaTime) override;
    
    void Render() override;
    void Init() override;
    virtual Position* GetPos() override
    {
        return &GetObject()->position;
    }

    void PushFrame(int animationID, SpriteFrame frame);
    void Play(int animationID);
    void SetAnimationLink(int animationID, int linkedAnimationID);
    void SetFlip(bool val);

private:
    std::map<int, std::vector<SpriteFrame>> animations;
    std::map<int, int> animationLinks;
    bool flip = false;
    int currentFrame = 0;
    int currentAnimation = 0;
    float timer = 0.0f;
};