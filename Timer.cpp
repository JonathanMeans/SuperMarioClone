#include "Timer.h"

#include <utility>

namespace
{
Timer gTimer;
}

Timer& getTimer()
{
    return gTimer;
}

void Timer::scheduleSeconds(double numSeconds, const std::function<void()>& callback)
{
    scheduledTimes.emplace_back(numFrames + numSeconds * FRAMES_PER_SECOND, callback);
}

void Timer::incrementNumFrames()
{
    for (int i = static_cast<int>(scheduledTimes.size() - 1); i >= 0; i--)
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
    mCallback(std::move(callback))
{
}



