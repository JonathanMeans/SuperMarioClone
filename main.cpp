#include "Mario.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include <file_util.h>

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

void collideWithGround(Mario& sprite, const size_t groundY)
{
    const auto spriteBottom = sprite.getBottomPosition();
    if (spriteBottom > groundY)
    {
        sprite.setBottomPosition(groundY);
        const auto currentVelocity = sprite.getVelocity();
        sprite.setVelocity(sf::Vector2f(currentVelocity.x, 0));
        sprite.setJumping(false);
    }
}

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

int main(int argc, char* argv[])
{
    const auto root = findRootDirectory(argv[0]);
    const auto resourceDir = root + "resources/";

    sf::RenderWindow window(sf::VideoMode(200, 200), "Super Mario Bros");
    window.setFramerateLimit(30);
    window.setSize(sf::Vector2u(960, 720));
    window.clear();
    Mario mario(resourceDir);
    mario.draw(window);
    window.display();

    KeyboardInput currentInput = {};
    KeyboardInput previousInput = {};

    const size_t groundY = mario.getY() + 20;

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
            mario.setForm(MarioForm::BIG_MARIO);
        }
        else if (currentInput.B.releasedThisFrame())
        {
            mario.setForm(MarioForm::SMALL_MARIO);
        }

        sf::Vector2f acceleration = mario.getAcceleration();
        sf::Vector2f velocity = mario.getVelocity();
        if (currentInput.A.keyIsDown)
        {
            mario.setJumping(true);
            velocity.y = -5;
        }

        if (currentInput.right.pressedThisFrame())
        {
            if (!currentInput.left.keyIsDown)
                acceleration.x = 1;
        }
        if (currentInput.left.pressedThisFrame())
        {
            if (!currentInput.right.keyIsDown)
                acceleration.x = -1;
        }
        if ((currentInput.left.releasedThisFrame() &&
             !currentInput.right.keyIsDown) ||
            (currentInput.right.releasedThisFrame() &&
             !currentInput.left.keyIsDown))
        {
            // TODO: Should we decelerate to 0?
            velocity.x = 0;
            acceleration.x = 0;
        }

        mario.setAcceleration(acceleration);
        mario.setVelocity(velocity);

        mario.updatePosition();
        collideWithGround(mario, groundY);

        mario.setAnimation();
        mario.updateAnimation();

        window.clear();
        mario.draw(window);
        window.display();
    }

    return 0;
}
