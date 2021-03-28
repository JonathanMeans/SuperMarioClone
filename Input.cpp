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
    switch(knownKey) {
        case sf::Keyboard::A:
            updateInputState(currentInput.A, previousInput.A, isPressed);
            break;
        case sf::Keyboard::S:
            updateInputState(currentInput.B, previousInput.B, isPressed);
            break;
        case sf::Keyboard::Right:
            updateInputState(currentInput.right,previousInput.right, isPressed);
            break;
        case sf::Keyboard::Left:
            updateInputState(currentInput.left, previousInput.left, isPressed);
            break;
        default:
            break;
    }
    previousInput = currentInput;
}