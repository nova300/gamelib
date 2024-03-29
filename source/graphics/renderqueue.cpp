#include "graphics/renderqueue.h"
#include "core/object.h"

#include <map>

std::vector<RenderQueue*> renderQueues;

RenderQueue::RenderQueue(int pass)
{
    SetPass(pass);
}

RenderQueue::~RenderQueue()
{
    UnsetPass();
}

void RenderQueue::SetPass(int pass)
{
    this->pass = pass;
    renderQueues.push_back(this);
}

void RenderQueue::UnsetPass()
{
    for(std::vector<RenderQueue*>::iterator it = renderQueues.begin(); it != renderQueues.end();)
    {
	    if(*it == this)
	    {
	    	it = renderQueues.erase(it);
	    }
	    else
	    {
	    	it++;
	    }
    }
}

void RenderQueue::Render()
{
    PreRender();
    for(auto obj : objects)
    {
        obj->Render();
        obj->RenderBehaviours();
    }
    PostRender();
}

void RenderQueue::RenderAll()
{
    for(auto q : renderQueues)
    {
        q->Render();
    }
}

void RenderQueue::Add(Object* obj)
{
    objects.push_back(obj);
}

void RenderQueue::Remove(Object* obj)
{
    for(std::vector<Object*>::iterator it = objects.begin(); it != objects.end();)
    {
	    if(*it == obj)
	    {
	    	it = objects.erase(it);
	    }
	    else
	    {
	    	it++;
	    }
    }
}