#include "graphics/renderqueue.h"
#include "core/object.h"
#include "libgame.h"
#include "utils/timekeep.h"

void RenderQueueVector::DrawRender()
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

void RenderQueueVector::AddRender(std::shared_ptr<GeoObject> obj)
{
    objects.push_back(obj);
}

void RenderQueueVector::RemoveRender(std::shared_ptr<GeoObject> obj)
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


void RenderQueueMap2D::DrawRender()
{
	auto timers = Timekeep::GetGlobalTimers();
	timers->rq1pre = GetTime();
	auto active = objects.GetAllActive();
	for(const auto& [index, o] : active)
	{
		if(!o->object.expired())
		{
			IntRectangle bounds = o->object.lock()->GetPos()->world.Rect();
			objects.Update(bounds, index);
		}
	}
	frameList.clear();
	PreListGen();
	frameList = objects.Get(renderBounds);
	timers->rq1pre = GetTime() - timers->rq1pre;
	timers->rq1pre2 = GetTime();
    PreRender();
	timers->rq1pre2 = GetTime() - timers->rq1pre2;
	timers->rq1draw = GetTime();
    for(auto n : frameList)
    {
		auto ptr = n->object.lock();
	    if(ptr != nullptr && !n->occluded)
	    {
			if(ptr->GetVisibility()) ptr->Render();
	    }
    }
	timers->rq1draw = GetTime() - timers->rq1draw;
	timers->rq1post = GetTime();
    PostRender();
	timers->rq1post = GetTime() - timers->rq1post;
}

void RenderQueueMap2D::AddRender(std::shared_ptr<GeoObject> obj)
{
	if(indicies.count(obj.get()) > 0) return;
    IntRectangle bounds = obj->GetPos()->world.Rect();

	RenderQueueMap2D::Node node;

	node.object = obj;
	node.occluded = false;

	unsigned int index = objects.Add(bounds, node);

	indicies[obj.get()] = index;

}

void RenderQueueMap2D::RemoveRender(std::shared_ptr<GeoObject> obj)
{
	if(indicies.count(obj.get()) < 1) LOG_RETURN("no geoobject to remove!");
    unsigned int index = indicies[obj.get()];

	objects.Remove(index);
	indicies.erase(obj.get());
}