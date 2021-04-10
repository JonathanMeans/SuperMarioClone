#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include "Entity.h"

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

extern const std::vector<sf::Keyboard::Key> ALL_KEYS;

void updateKeyboardInputs(KeyboardInput& currentInput,
                          KeyboardInput& previousInput,
                          sf::Keyboard::Key knownKey,
                          bool isPressed);

std::vector<KeyboardInput> generateInputs(
        const std::vector<std::vector<sf::Keyboard::Key>>& keyInputs);

KeyboardInput nextInput(std::vector<KeyboardInput> keyboardInputs, size_t idx);

#endif
