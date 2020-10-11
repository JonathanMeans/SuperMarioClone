#include "Goomba.h"
#include "Mario.h"
#include "SpriteMaker.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include <file_util.h>
#include <iostream>

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

int main(int argc, char* argv[])
{
    const auto root = findRootDirectory(argv[0]);
    const auto resourceDir = root + "resources/";

    sf::RenderWindow window(sf::VideoMode(200, 200), "Super Mario Bros");
    window.setFramerateLimit(30);
    window.setSize(sf::Vector2u(960, 720));
    window.clear();

    SpriteMaker spriteMaker(resourceDir);
    Mario mario(spriteMaker.marioSprite);
    Goomba goomba(spriteMaker.goombaSprite);

    std::vector<Entity> enemies;
    enemies.push_back(goomba);

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
        for (auto& enemy : enemies)
            enemy.updatePosition();
        mario.collideWithGround(groundY);
        for (auto& enemy : enemies)
            enemy.collideWithGround(groundY);
        mario.collideWithEnemy(enemies);

        mario.updateAnimation();

        for (auto& enemy : enemies)
            enemy.updateAnimation();

        window.clear(sf::Color(0, 0, 255, 255));
        mario.draw(window);
        goomba.draw(window);
        window.display();
    }

    return 0;
}
