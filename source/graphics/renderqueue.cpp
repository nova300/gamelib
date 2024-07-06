#include "graphics/renderqueue.h"
#include "core/object.h"

void RenderQueue::DrawRender()
{
    PreRender();
    for(std::vector<std::weak_ptr<GeoObject>>::iterator it = objects.begin(); it != objects.end();)
    {
	    if(it->expired())
	    {
	    	it = objects.erase(it);
	    }
	    else
	    {
	    	auto obj = it->lock();
			if(obj->GetVisibility()) obj->Render();
			it++;
	    }
    }
    PostRender();
}

void RenderQueue::AddRender(std::shared_ptr<GeoObject> obj)
{
    objects.push_back(obj);
}

void RenderQueue::RemoveRender(std::shared_ptr<GeoObject> obj)
{
    for(std::vector<std::weak_ptr<GeoObject>>::iterator it = objects.begin(); it != objects.end();)
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