#include "core/object.h"

void Object::AwakeBehaviours()
{
    for(auto& b : behaviours)
    {
        b->Awake();
    }
}

void Object::InitBehaviours()
{
    for(auto& b : behaviours)
    {
        b->Init();
    }
}

void Object::UpdateBehaviours(float deltaTime)
{
    for(auto& b : behaviours)
    {
        b->Update(deltaTime);
    }
}

void Object::LateUpdateBehaviours(float deltaTime)
{
    for(auto& b : behaviours)
    {
        b->LateUpdate(deltaTime);
    }
}

void Object::RenderBehaviours()
{
    for(auto& b : behaviours)
    {
        b->Render();
    }
}