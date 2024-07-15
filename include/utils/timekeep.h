#pragma once

namespace Timekeep
{
    struct Timers
    {
        float rendertime;
        float updatetime;
        float rq1time;
        float rq1pre;
        float rq1pre2;
        float rq1draw;
        float rq1post;
    };

    Timers* GetGlobalTimers();

    void DrawTimers();
    
};