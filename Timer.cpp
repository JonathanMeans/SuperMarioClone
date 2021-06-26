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

void Timer::scheduleSeconds(double numSeconds,
                            const std::function<void()>& callback)
{
    scheduledTimes.emplace_back(numFrames + numSeconds * FRAMES_PER_SECOND,
                                callback);
}

void Timer::scheduleEveryNSeconds(double numSeconds,
                                  const std::function<void()>& callback)
{
    repeatedTimes.emplace_back(numSeconds * FRAMES_PER_SECOND,
                               numFrames,
                               callback);
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
    for (int i = static_cast<int>(repeatedTimes.size() - 1); i >= 0; i--)
    {
        auto event = repeatedTimes[i];
        if (numFrames == event.mTime + event.mStartingNumFrames)
        {
            event.mCallback();
            repeatedTimes[i].mStartingNumFrames = numFrames;
        }
    }
    numFrames += 1;
}

ScheduledEvent::ScheduledEvent(size_t time, std::function<void()> callback) :
    mTime(time),
    mCallback(std::move(callback))
{
}
RecurringEvent::RecurringEvent(size_t time,
                               size_t startingNumFrames,
                               std::function<void()> callback) :
    mTime(time),
    mStartingNumFrames(startingNumFrames),
    mCallback(std::move(callback))
{
}
