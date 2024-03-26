#include "graphics/renderqueue.h"

#include <map>

std::multimap<int, RenderQueue*> renderqueues;

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
    for(auto val : objects)
    {
        auto [pos, obj] = val;
        obj->Render();
        obj->RenderBehaviours();
    }
}

void RenderQueue::RenderAll()
{
    for(auto val : renderqueues)
    {
        auto [pass, queue] = val;
        queue->Draw();
    }
}

void RenderQueue::Add(std::shared_ptr<Object> obj, int pos)
{
    objects.emplace(pos, obj);
}

void RenderQueue::Remove(std::shared_ptr<Object> obj)
{
    for(std::map<int, std::shared_ptr<Object>>::iterator it = objects.begin(); it != objects.end();)
    {
	    if((it->second) == obj)
	    {
	    	it = objects.erase(it);
	    }
	    else
	    {
	    	it++;
	    }
    }
}