//
// Created by jon on 11/22/20.
//

#ifndef SUPERMARIOBROS_TIMER_H
#define SUPERMARIOBROS_TIMER_H

#include <cstddef>
#include <functional>

class Timer
{
public:
    void scheduleSeconds(size_t numSeconds, std::function<void()> callback);
};

Timer& getTimer();



#endif  // SUPERMARIOBROS_TIMER_H
