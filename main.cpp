#include <file_util.h>

#include "Goomba.h"
#include "Input.h"
#include "Level.h"
#include "Mario.h"
#include "Pipe.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SpriteMaker.h"
#include "Timer.h"

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
    std::unique_ptr<Mario> mario(new Mario(spriteMaker.marioSprite, {30, 100}));
    std::unique_ptr<Goomba> goomba(new Goomba(spriteMaker.goombaSprite, {150, 50}));
    std::unique_ptr<Pipe> leftPipe(new Pipe(spriteMaker.pipeSprite, {110, 100}));

    std::vector<Entity*> entities;
    entities.push_back(goomba.get());
    entities.push_back(leftPipe.get());

    float groundHeight = mario->getTop() + 20;
    Level level(std::move(mario), entities, groundHeight);

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

        level.executeFrame(currentInput);
        level.drawFrame(window);
        window.display();

        getTimer().incrementNumFrames();
    }

    return 0;
}
