#include <file_util.h>

#include "Input.h"
#include "Level.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SpriteMaker.h"
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

    SpriteMaker spriteMaker(resourceDir);
    std::vector<std::unique_ptr<Entity>> entities;
    entities.reserve(100);

    std::unique_ptr<Mario> mario(
            new Mario(spriteMaker.playerTexture, {60, 100}));
    std::unique_ptr<Goomba> goomba(
            new Goomba(spriteMaker.enemyTexture, {150, 50}));
    std::unique_ptr<Pipe> leftPipe(
            new Pipe(spriteMaker.inanimateObjectTexture, {110, 100}));
    std::unique_ptr<Pipe> rightPipe(
            new Pipe(spriteMaker.inanimateObjectTexture, {-10, 100}));

    entities.push_back(std::move(leftPipe));
    entities.push_back(std::move(rightPipe));
    entities.push_back(std::move(goomba));

    for (int i = 0; i < 20; i++)
    {
        entities.push_back(
                std::make_unique<Ground>(spriteMaker.inanimateObjectTexture,
                                         sf::Vector2f(i * 16, 132)));
    }

    entities.push_back(
            std::make_unique<Block>(spriteMaker.inanimateObjectTexture,
                                    sf::Vector2f(40, 70)));

    Level level(std::move(mario), std::move(entities));

    KeyboardInput currentInput = {};
    KeyboardInput previousInput = {};

    std::vector<KeyboardInput> keyboardInputs;
    keyboardInputs = generateInputs({{sf::Keyboard::Right},
                                     {sf::Keyboard::Right},
                                     {sf::Keyboard::Right},
                                     {sf::Keyboard::Right},
                                     {sf::Keyboard::Right},
                                     {sf::Keyboard::Right},
                                     {sf::Keyboard::Right},
                                     {sf::Keyboard::Right},
                                     {sf::Keyboard::Right},
                                     {sf::Keyboard::Right},
                                     {sf::Keyboard::Right},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left, sf::Keyboard::A},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left},
                                     {sf::Keyboard::Left}});
    int idx = 0;
    while (window.isOpen())
    {
        sf::Event event = {};
#ifdef MANUAL_INPUT
        currentInput = nextInput(keyboardInputs, idx);
        ++idx;
#endif
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
#ifndef MANUAL_INPUT
            case sf::Event::KeyPressed:
                updateKeyboardInputs(currentInput,
                                     previousInput,
                                     event.key.code,
                                     true);
                break;
            case sf::Event::KeyReleased:
                updateKeyboardInputs(currentInput,
                                     previousInput,
                                     event.key.code,
                                     false);
                break;
#endif
            default:
                break;
            }
        }

        level.executeFrame(currentInput);
        level.drawFrame(window);
        window.display();

        getTimer().incrementNumFrames();
    }
    return 0;
}
