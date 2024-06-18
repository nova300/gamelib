#include "graphics/renderqueue.h"
#include "core/object.h"

void RenderQueue::DrawRender()
{
    PreRender();
    for(std::vector<std::weak_ptr<Object>>::iterator it = objects.begin(); it != objects.end();)
    {
	    if(it->expired())
	    {
	    	it = objects.erase(it);
	    }
	    else
	    {
	    	auto obj = it->lock();
            obj->Render();
            obj->RenderBehaviours();
	    }
    }
    PostRender();
}

void RenderQueue::AddRender(std::shared_ptr<Object> obj)
{
    objects.push_back(obj);
}

void RenderQueue::RemoveRender(std::shared_ptr<Object> obj)
{
    for(std::vector<std::weak_ptr<Object>>::iterator it = objects.begin(); it != objects.end();)
    {
	    if(it->lock() == obj)
	    {
	    	it = objects.erase(it);
	    }
	    else
	    {
	    	it++;
	    }
    }
}