#include "core/objectstore.h"

void ObjectStore::Update(float deltaTime)
{
    for(auto& o : objects)
    {
        o->Update(deltaTime);
        o->UpdateBehaviours(deltaTime);
    }
}

void ObjectStore::LateUpdate(float deltaTime)
{
    for(auto& o : objects)
    {
        o->LateUpdate(deltaTime);
        o->LateUpdateBehaviours(deltaTime);
    }
}

void ObjectStore::Add(std::shared_ptr<Object> obj)
{
    newObjects.push_back(obj);
}

void ObjectStore::ProcessNewObjects()
{
    if(newObjects.size() > 0)
    {
        for(const auto& o : newObjects)
        {
            o->Awake();
            o->AwakeBehaviours();
        }

        for(const auto& o : newObjects)
        {
            o->Init();
            o->InitBehaviours();
        }

        objects.assign(newObjects.begin(), newObjects.end());

        newObjects.clear();
    }
}