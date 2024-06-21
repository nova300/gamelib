#include "core/object.h"
#include <iostream>

//attach already existing object as child
void Object::AddChild(std::shared_ptr<Object> obj)
{
    //safety checks
    if(obj.get() == this) { std::cout << "Object::AddChild: ERROR: cannot add object to itself" << std::endl; return; }
    if(obj.get() == nullptr) { std::cout << "Object::AddChild: ERROR: cannot add null object" << std::endl; return; }
    if(obj.get() == parent) { std::cout << "Object::AddChild: ERROR: cannot add parent to child" << std::endl; return; }
    if(obj->parent != nullptr) { std::cout << "Object::AddChild: ERROR: object already has parent!" << std::endl; return; }

    for(const auto o : childObjects)
    {
        if(obj == o) { std::cout << "Object::AddChild: ERROR: is already child" << std::endl; return; }
    }
    for(const auto o : newchildObjects)
    {
        if(obj == o) { std::cout << "Object::AddChild: ERROR: is already child (new)" << std::endl; return; }
    }

    //attach object
    obj->program = program;
    obj->parent = this;
    obj->level = level + 1;

    newchildObjects.push_back(obj);
}

void Object::RemoveChild(std::shared_ptr<Object> obj)
{
    if(obj.get() == nullptr) { std::cout << "Object::RemoveChild: ERROR: cannot remove null object" << std::endl; return; }

    bool ok = false;

    for(std::vector<std::shared_ptr<Object>>::iterator it = childObjects.begin(); it != childObjects.end();)
    {
	    if(*it == obj)
	    {
	    	it = childObjects.erase(it);
            ok = true;
	    }
	    else
	    {
	    	it++;
	    }
    }

    if(ok)
    {
        obj->level = 0;
        obj->parent = nullptr;
    }

}

void Object::UpdateWorldPos()
{
    if(parent)
    {
        Engine::Transform outp = parent->position.world;
        outp.position = Vector3Add(outp.position, position.local.position);
        outp.rotation = Vector3Add(outp.rotation, position.local.rotation);
        outp.scale = Vector3Multiply(outp.scale, position.local.scale);
        outp.size = position.local.size;
        position.world = outp;
    }
    else
    {
        position.world = position.local;
    }
}

void Object::UpdateInternal(float deltaTime)
{
    UpdateWorldPos();
    if(newbehaviours.size() > 0)
    {
        for(const auto o : newbehaviours)
        {
            o->Init();
        }

        behaviours.assign(newbehaviours.begin(), newbehaviours.end());

        newbehaviours.clear();
    }

    if(newchildObjects.size() > 0)
    {
        for(const auto o : newchildObjects)
        {
            o->Init();
        }

        childObjects.assign(newchildObjects.begin(), newchildObjects.end());

        newchildObjects.clear();
    }

//self
    Update(deltaTime);
    for(auto& b : behaviours)
    {
        b->Update(deltaTime);
    }

//childs
    for(auto& b : childObjects)
    {
        b->UpdateInternal(deltaTime);
    }
}

void Object::PostUpdateInternal(float deltaTime)
{
    UpdateWorldPos();
//self
    PostUpdate(deltaTime);
    for(auto& b : behaviours)
    {
        b->PostUpdate(deltaTime);
    }

//childs
    for(auto& b : childObjects)
    {
        b->PostUpdateInternal(deltaTime);
    }
}

/*void Object::RenderInternal()
{
    Render();
    for(auto& b : behaviours)
    {
        b->Render();
    }

}*/