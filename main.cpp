#include "Mario.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

struct KeyboardInputState
{
    bool keyIsDown;
    bool keyWasDown;

    [[nodiscard]] bool pressedThisFrame() const
    {
        return keyIsDown && !keyWasDown;
    }

    [[nodiscard]] bool releasedThisFrame() const
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

void updateInputState(KeyboardInputState& currentState,
                      const KeyboardInputState& previousState,
                      const sf::Keyboard::Key key)
{
    currentState.keyWasDown = previousState.keyIsDown;
    currentState.keyIsDown = sf::Keyboard::isKeyPressed(key);
}

void updateKeyboardInputs(KeyboardInput& currentInput,
                          KeyboardInput& previousInput)
{
    updateInputState(currentInput.A, previousInput.A, sf::Keyboard::A);
    updateInputState(currentInput.B, previousInput.B, sf::Keyboard::S);
    updateInputState(currentInput.right,
                     previousInput.right,
                     sf::Keyboard::Right);

    updateInputState(currentInput.left, previousInput.left, sf::Keyboard::Left);
    previousInput = currentInput;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Super Mario Bros");
    window.setFramerateLimit(30);
    window.setSize(sf::Vector2u(960, 720));
    window.clear();
    Mario sprite;
    sprite.draw(window);
    window.display();

    KeyboardInput currentInput = {};
    KeyboardInput previousInput = {};

    while (window.isOpen())
    {
        sf::Event event = {};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        updateKeyboardInputs(currentInput, previousInput);

        if (currentInput.B.pressedThisFrame())
        {
            sprite.setForm(MarioForm::BIG_MARIO);
        }
        else if (currentInput.B.releasedThisFrame())
        {
            sprite.setForm(MarioForm::SMALL_MARIO);
        }

        sf::Vector2f deltaVelocity = sprite.getVelocity();
        if (currentInput.A.keyIsDown)
        {
            sprite.jump();
        }
        else
        {
            if (currentInput.right.pressedThisFrame())
            {
                if (!currentInput.left.keyIsDown)
                    deltaVelocity.x = 1;
            }
            if (currentInput.left.pressedThisFrame())
            {
                if (!currentInput.right.keyIsDown)
                    deltaVelocity.x = -1;
            }
            if (currentInput.left.releasedThisFrame() ||
                currentInput.right.releasedThisFrame())
            {
                deltaVelocity.x = 0;
            }
        }

        sprite.setVelocity(deltaVelocity);

        sprite.updatePosition();
        sprite.updateAnimation();
        window.clear();
        sprite.draw(window);
        window.display();
    }

    return 0;
}