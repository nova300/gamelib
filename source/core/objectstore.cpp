#include "core/objectstore.h"
#include <stdio.h>

void ObjectStore::UpdateObjects(float deltaTime)
{
    for(auto& o : objects)
    {
        o->Update(deltaTime);
        o->UpdateBehaviours(deltaTime);
    }
}

void ObjectStore::PostUpdateObjects(float deltaTime)
{
    for(auto& o : objects)
    {
        o->PostUpdate(deltaTime);
        o->PostUpdateBehaviours(deltaTime);
    }
}

void ObjectStore::AddObject(Object* obj)
{
    newObjects.push_back(obj);
}

void ObjectStore::RemoveObject(Object* obj)
{
    int n = 0;
    for(std::vector<Object*>::iterator it = objects.begin(); it != objects.end();)
    {
	    if(*it == obj)
	    {
	    	it = objects.erase(it);
            n++;
	    }
	    else
	    {
	    	it++;
	    }
    }

    printf("OBJECTSTORE: Removed %i objects\n", n);
}

void ObjectStore::ProcessNewObjects()
{
    if(newObjects.size() > 0)
    {
        int awakes = 0;
        for(const auto o : newObjects)
        {
            o->Awake();
            o->AwakeBehaviours();
            awakes++;
        }
        printf("OBJECTSTORE: Awoke %i objects\n", awakes);

        int inits = 0;
        for(const auto o : newObjects)
        {
            o->Init();
            o->InitBehaviours();
            inits++;
        }
        printf("OBJECTSTORE: Initialized %i objects\n", inits);

        objects.assign(newObjects.begin(), newObjects.end());

        newObjects.clear();
    }
}