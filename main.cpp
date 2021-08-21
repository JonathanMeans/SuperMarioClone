#include <entities/InvisibleWall.h>
#include <file_util.h>

#include "ControllerOverlay.h"
#include "Input.h"
#include "Level.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SpriteMaker.h"
#include "Text.h"
#include "Timer.h"
#include "entities/Block.h"
#include "entities/Goomba.h"
#include "entities/Ground.h"
#include "entities/Mario.h"
#include "entities/Pipe.h"

int main(int argc, char* argv[])
{
    const auto root = findRootDirectory(argv[0]);
    const auto resourceDir = root + "resources/";

    sf::RenderWindow window(sf::VideoMode(200, 200), "Super Mario Bros");
    window.setFramerateLimit(30);
    window.setSize(sf::Vector2u(960, 720));
    window.clear();

    initializeSpriteMaker(resourceDir);
    initializeHUDOverlay(resourceDir);

    auto& spriteMaker = getSpriteMaker();

    std::vector<std::unique_ptr<Entity>> entities;
    entities.reserve(100);

    std::unique_ptr<Mario> mario(
            new Mario(spriteMaker->playerTexture, {60, 90}));
    std::unique_ptr<Goomba> goomba(
            new Goomba(spriteMaker->enemyTexture, {150, 50}));
    std::unique_ptr<Pipe> rightPipe(
            new Pipe(spriteMaker->inanimateObjectTexture, {130, 116}));
    std::unique_ptr<Pipe> leftPipe(
            new Pipe(spriteMaker->inanimateObjectTexture, {-10, 116}));

    entities.push_back(std::move(leftPipe));
    entities.push_back(std::move(rightPipe));
    entities.push_back(std::move(goomba));

    entities.push_back(
            std::make_unique<InvisibleWall>(spriteMaker->inanimateObjectTexture,
                                            sf::Vector2f(-16, -500)));
    auto& wall = *(
            dynamic_cast<InvisibleWall*>(entities[entities.size() - 1].get()));

    for (int i = 0; i < 20; i++)
    {
        entities.push_back(
                std::make_unique<Ground>(spriteMaker->inanimateObjectTexture,
                                         sf::Vector2f(i * 16, 132)));
    }

    entities.push_back(std::make_unique<BreakableBlock>(
            spriteMaker->inanimateObjectTexture, sf::Vector2f(40, 70)));
    entities.push_back(
            std::make_unique<ItemBlock>(spriteMaker->inanimateObjectTexture,
                                        sf::Vector2f(56, 70)));
    entities.push_back(
            std::make_unique<ItemBlock>(spriteMaker->inanimateObjectTexture,
                                        sf::Vector2f(72, 70)));

    Level level(std::move(mario), std::move(entities), window, wall);

    KeyboardInput currentInput = {};
    KeyboardInput previousInput = {};

    std::vector<KeyboardInput> keyboardInputs;
    while (window.isOpen())
    {
        sf::Event event = {};
#ifdef MANUAL_INPUT
        currentInput = nextInput(keyboardInputs, idx);
        ++idx;
#endif
        std::vector<sf::Keyboard::Key> keycodes;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
#ifndef MANUAL_INPUT
            case sf::Event::KeyPressed:
                currentInput.setKey(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
            {
                currentInput.setKey(event.key.code, false);
                break;
            }
#endif
            default:
                break;
            }
        }
        currentInput.updateWasDown(previousInput);
        previousInput = currentInput;

        level.executeFrame(currentInput);
        level.drawFrame(window);
        // Comment/uncomment line below to display in-game controller
        ControllerOverlay::draw(currentInput, window);
        window.display();

        getTimer().incrementNumFrames();
    }
    return 0;
}
