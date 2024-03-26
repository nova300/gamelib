#pragma once

#include "graphics/renderqueue.h"
#include <raylib.h>

class FrameBufferQueue : public RenderQueue, public Object
{
public:
    RenderTexture2D framebuffer;
};