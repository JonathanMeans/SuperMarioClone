#include "Input.h"

#include <SFML/Window/Keyboard.hpp>

void updateInputState(KeyboardInputState& currentState,
                      const KeyboardInputState& previousState,
                      bool isPressed)
{
    currentState.keyWasDown = previousState.keyIsDown;
    currentState.keyIsDown = isPressed;
}

void updateKeyboardInputs(KeyboardInput& currentInput,
                          KeyboardInput& previousInput,
                          sf::Keyboard::Key knownKey,
                          bool isPressed)
{
    switch (knownKey)
    {
    case sf::Keyboard::A:
        updateInputState(currentInput.A, previousInput.A, isPressed);
        break;
    case sf::Keyboard::S:
        updateInputState(currentInput.B, previousInput.B, isPressed);
        break;
    case sf::Keyboard::Right:
        updateInputState(currentInput.right, previousInput.right, isPressed);
        break;
    case sf::Keyboard::Left:
        updateInputState(currentInput.left, previousInput.left, isPressed);
        break;
    default:
        break;
    }
    previousInput = currentInput;
}

std::vector<KeyboardInput> generateInputs(const std::vector<std::vector<sf::Keyboard::Key>> &keyInputs) {
    std::vector<KeyboardInput> result;
    KeyboardInput prevInput = {};

    for (const auto& frameInputs : keyInputs) {
        KeyboardInput keyboardInput = {};
        for (const auto& key: frameInputs) {
            updateKeyboardInputs(keyboardInput, prevInput, key, true);
        }
        prevInput = keyboardInput;
        result.push_back(keyboardInput);
    }
    return result;
}

KeyboardInput nextInput(std::vector<KeyboardInput> keyboardInputs, size_t idx) {
    return idx < keyboardInputs.size() ? keyboardInputs[idx] : KeyboardInput{};
}