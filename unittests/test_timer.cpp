#include <gtest/gtest.h>
#include "Timer.h"

TEST(Timer, ExecuteCallbackAfterOneSecond)
{
    Timer timer;
    size_t dummy = 0;
    timer.scheduleSeconds(1, [&]() { dummy = 1; });
    for (int i = 0; i <= timer.FRAMES_PER_SECOND; i++)
    {
        timer.incrementNumFrames();
    }
    EXPECT_EQ(dummy, 1);
}

TEST(Timer, CannotExecuteCallback)
{
    Timer timer;
    size_t dummy = 0;
    timer.scheduleSeconds(1, [&]() { dummy = 1; });
    for (int i = 0; i < timer.FRAMES_PER_SECOND; i++)
    {
        timer.incrementNumFrames();
    }
    EXPECT_EQ(dummy, 0);
}



