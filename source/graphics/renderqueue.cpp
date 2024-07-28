#include "graphics/renderqueue.h"
#include "core/object.h"
#include "libgame.h"
#include "utils/timekeep.h"
#include "utils/math.h"

void RenderQueueVector::DrawRender()
{
    PreRender();
	Timekeep::Timer timer = Timekeep::Timer("RQV TOTAL");
	timer.Begin();
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
	timer.End();
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
	Timekeep::Timer timer1 = Timekeep::Timer("RQM2D GET");
	Timekeep::Timer timer2 = Timekeep::Timer("RQM2D LIST");
	Timekeep::Timer timer3 = Timekeep::Timer("RQM2D PRE");
	Timekeep::Timer timer4 = Timekeep::Timer("RQM2D DRAW");
	Timekeep::ScopeTimer timer5 = Timekeep::ScopeTimer("RQM2D TOTAL");
	Timekeep::Timer timer6 = Timekeep::Timer("RQM2D UPDATE");

	timer1.Begin();
	auto& active = objects.storage.GetVector();
	timer1.End();

	timer6.Begin();
	for(const auto& d : active)
	{
		if(d.index < 0) continue;
		if(!d.value.value.object.expired())
		{
			IntRectangle bounds = d.value.value.object.lock()->GetPos()->world.Rect();
			objects.Update(bounds, d.index);
		}
	}
	timer6.End();

	timer2.Begin();
	frameList.clear();
	PreListGen();
	frameList = objects.Get(renderBounds);
	timer2.End();

	timer3.Begin();
    PreRender();
	timer3.End();

	timer4.Begin();
    for(auto n : frameList)
    {
		auto ptr = n->object.lock();
	    if(ptr != nullptr && !n->occluded)
	    {
			if(ptr->GetVisibility()) ptr->Render();
	    }
    }
	timer4.End();
	
    PostRender();
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

void RenderQueueMap2DCam::PreListGen()
{
    if(camera)
    {
        const float offset = 0.0f;
        auto newBounds = GetCameraBounds(*camera, offset);
        renderBounds = newBounds;
    }
    
}


void RenderQueueMap2DCam::PreRender()
{
    BeginMode2D(*camera);
    
}

void RenderQueueMap2DCam::PostRender()
{
    EndMode2D();
}