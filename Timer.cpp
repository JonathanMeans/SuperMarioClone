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

    scheduledTimes.push_back(ScheduledEvent(numFrames + numSeconds * FRAMES_PER_SECOND, callback));
}

void Timer::incrementNumFrames()
{
    for (int i = scheduledTimes.size() - 1; i >= 0; i--)
    {
        ScheduledEvent event = scheduledTimes[i];
        if (numFrames == event.mTime)
        {
            event.mCallback();
            scheduledTimes.erase(scheduledTimes.begin() + i);
        }
    }
    numFrames += 1;
}

ScheduledEvent::ScheduledEvent(size_t time, std::function<void()> callback) :
    mTime(time),
    mCallback(callback)
{
}



