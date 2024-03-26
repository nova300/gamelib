#include "graphics/renderqueue.h"
#include "core/object.h"

#include <map>

std::multimap<int, RenderQueue*> renderqueues;

RenderQueue::RenderQueue(int pass)
{
    renderqueues.emplace(pass, this);
}

RenderQueue::~RenderQueue()
{
    UnsetPass();
}

void RenderQueue::SetPass(int pass)
{
    renderqueues.emplace(pass, this);
}

void RenderQueue::UnsetPass()
{
    for(std::map<int, RenderQueue*>::iterator it = renderqueues.begin(); it != renderqueues.end();)
    {
	    if((it->second) == this)
	    {
	    	it = renderqueues.erase(it);
	    }
	    else
	    {
	    	it++;
	    }
    }
}

void RenderQueue::Draw()
{
    if(camera2d != nullptr) BeginMode2D(*camera2d.get());
    for(auto val : objects)
    {
        auto [pos, obj] = val;
        if(!obj.expired())
        {
            auto obj1 = obj.lock();
            obj1->Render();
            obj1->RenderBehaviours();
        }
    }
    if(camera2d != nullptr) EndMode2D();
}

void RenderQueue::RenderAll()
{
    for(auto val : renderqueues)
    {
        auto [pass, queue] = val;

        queue->Draw();

    }
}

void RenderQueue::Add(std::shared_ptr<Object> obj, float pos)
{
    objects.emplace(pos, obj);
}

void RenderQueue::Remove(std::shared_ptr<Object> obj)
{
    for(std::map<float, std::weak_ptr<Object>>::iterator it = objects.begin(); it != objects.end();)
    {
        if((it->second.expired()))
        {
            it = objects.erase(it);
        }
	    if((it->second.lock()) == obj)
	    {
	    	it = objects.erase(it);
	    }
	    else
	    {
	    	it++;
	    }
    }
}