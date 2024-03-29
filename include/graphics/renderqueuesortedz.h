#pragma once

#include "graphics/renderqueue.h"

class RenderQueueSortedZ : public RenderQueue
{
public:
    void PreRender() override;
    void PostRender() override;
};