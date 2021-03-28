#include <file_util.h>

#include "Input.h"
#include "Level.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SpriteMaker.h"
#include "Timer.h"
#include "entities/Block.h"
#include "entities/Goomba.h"
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
    std::vector<std::unique_ptr<Entity>> entities(23);

    std::unique_ptr<Mario> mario(new Mario(spriteMaker.marioSprite, {30, 100}));
    std::unique_ptr<Goomba> goomba(
            new Goomba(spriteMaker.goombaSprite, {150, 50}));
    std::unique_ptr<Pipe> leftPipe(
            new Pipe(spriteMaker.pipeSprite, {110, 100}));
    std::unique_ptr<Pipe> rightPipe(
            new Pipe(spriteMaker.pipeSprite, {-10, 100}));

    entities[0] = std::move(leftPipe);
    entities[1] = std::move(rightPipe);
    entities[2] = std::move(goomba);

    for (int i = 0; i < 20; i++)
    {
        entities[3 + i] = std::make_unique<Block>(spriteMaker.blockSprite,
                                                  sf::Vector2f(i * 16, 132));
    }

    Level level(std::move(mario), std::move(entities));

    KeyboardInput currentInput = {};
    KeyboardInput previousInput = {};

    while (window.isOpen())
    {
        sf::Event event = {};
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                updateKeyboardInputs(currentInput, previousInput, event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                updateKeyboardInputs(currentInput, previousInput, event.key.code, false);
                break;
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
