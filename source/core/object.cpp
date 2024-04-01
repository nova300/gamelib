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

void Object::PostUpdateBehaviours(float deltaTime)
{
    for(auto& b : behaviours)
    {
        b->PostUpdate(deltaTime);
    }
}

void Object::RenderBehaviours()
{
    for(auto& b : behaviours)
    {
        b->Render();
    }
}

/*void Object::SoftRenderBehaviours()
{
    for(auto& b : behaviours)
    {
        b->SoftRender();
    }
}*/