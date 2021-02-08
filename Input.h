#ifndef INPUT_H
#define INPUT_H

struct KeyboardInputState
{
    bool keyIsDown;
    bool keyWasDown;

    [[nodiscard]] inline bool pressedThisFrame() const
    {
        return keyIsDown && !keyWasDown;
    }

    [[nodiscard]] inline bool releasedThisFrame() const
    {
        return !keyIsDown && keyWasDown;
    }
};

struct KeyboardInput
{
    KeyboardInputState A;
    KeyboardInputState B;
    KeyboardInputState up;
    KeyboardInputState down;
    KeyboardInputState left;
    KeyboardInputState right;

    KeyboardInputState select;
    KeyboardInputState start;
};

#endif
