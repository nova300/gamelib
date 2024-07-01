// gui common
#include "gui/gui.h"


void WindowManager::MouseInput(Vector2 mousePos)
{
    for(std::vector<std::weak_ptr<GeoObject>>::iterator it = objects.begin(); it != objects.end();)
    {
	    if(it->expired())
	    {
	    	it = objects.erase(it);
	    }
	    else
	    {
	    	auto obj = it->lock();
            if(obj->MouseInput(mousePos)) break;
			it++;
	    }
    }
}


// gui modules
#include "window.cpp"