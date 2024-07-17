#pragma once
#include <raylib.h>
#include <string>

namespace Timekeep
{
    void AddTimerForFrame(std::string name, float time);
    void DrawTimers(const int posX, const int posY, const int size);

    class Timer
    {
    private:
        float timer = 0.0f;
        std::string name;

    public:
        Timer(std::string NAME)
        {
            name = NAME;
        }
        void Begin()
        {
            timer = GetTime();
        }
        void End()
        {
            timer = GetTime() - timer;
            AddTimerForFrame(name, timer);
        }
    };

    class ScopeTimer
    {
    private:
        float timer = 0.0f;
        std::string name;
    public:
        ScopeTimer(std::string NAME)
        {
            name = NAME;
            timer = GetTime();
        }
        ~ScopeTimer()
        {
            timer = GetTime() - timer;
            AddTimerForFrame(name, timer);
        }
    };

    
};