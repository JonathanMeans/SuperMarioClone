#include "Input.h"

#include <SFML/Window/Keyboard.hpp>
#include <vector>

const std::vector<sf::Keyboard::Key> ALL_KEYS = {sf::Keyboard::Left, sf::Keyboard::Right,
sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::A, sf::Keyboard::S};

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
    auto nullTerminatedKeyInputs(keyInputs);
    nullTerminatedKeyInputs.emplace_back();
    for (const auto& frameInputs : nullTerminatedKeyInputs) {
        KeyboardInput keyboardInput = {};
        for (const auto& key: ALL_KEYS) {
            updateKeyboardInputs(keyboardInput, prevInput, key,
                                 std::find(frameInputs.begin(), frameInputs.end(), key) != frameInputs.end());
        }
        prevInput = keyboardInput;
        result.push_back(keyboardInput);
    }
    return result;
}

KeyboardInput nextInput(std::vector<KeyboardInput> keyboardInputs, size_t idx) {
    return idx < keyboardInputs.size() ? keyboardInputs[idx] : KeyboardInput{};
}