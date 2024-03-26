#include "core/object.h"

bool Object::Active()
{
    return active;
}

bool Object::Visible()
{
    return visible;
}

void Object::Active(bool value)
{
    active = value;
}

void Object::Visible(bool value)
{
    visible = value;
}

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