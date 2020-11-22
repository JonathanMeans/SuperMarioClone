#include "Timer.h"

namespace
{
Timer gTimer;
}

Timer& getTimer()
{
    return gTimer;
}

void Timer::scheduleSeconds(size_t numSeconds, std::function<void()> callback)
{
    (void) numSeconds;
    (void) callback;
}
