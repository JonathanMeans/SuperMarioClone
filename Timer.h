//
// Created by jon on 11/22/20.
//

#ifndef SUPERMARIOBROS_TIMER_H
#define SUPERMARIOBROS_TIMER_H

#include <cstddef>
#include <functional>
#include <vector>

class ScheduledEvent
{
public:
    double mTime;
    std::function<void()> mCallback;

    ScheduledEvent(size_t time, std::function<void()> callback);
};

class RecurringEvent
{
public:
    double mTime;
    double mStartingNumFrames;
    std::function<void()> mCallback;

    RecurringEvent(size_t time, size_t startingNumFrames, std::function<void()> callback);
};

class Timer
{
public:
    void scheduleSeconds(double numSeconds, const std::function<void()>& callback);
    void scheduleEveryNSeconds(double numSeconds, const std::function<void()>& callback);
    void incrementNumFrames();

    size_t numFrames;
    std::vector<ScheduledEvent> scheduledTimes;
    std::vector<RecurringEvent> repeatedTimes;

    const size_t FRAMES_PER_SECOND = 30;
};

Timer& getTimer();


#endif  // SUPERMARIOBROS_TIMER_H
