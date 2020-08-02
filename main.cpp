#include "Mario.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Super Mario Bros");
    window.setFramerateLimit(30);
    window.setSize(sf::Vector2u(960, 720));
    window.clear();
    Mario sprite;
    sprite.draw(window);
    window.display();

    while (window.isOpen())
    {
        sf::Event event = {};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            sprite.grow();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            sprite.jump();
        }
        else
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                sprite.setPosition(sprite.getX() + 1, sprite.getY());
                sprite.walk();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                sprite.setPosition(sprite.getX() - 1, sprite.getY());
                sprite.walk();
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                sprite.stopWalking();
        }

        window.clear();
        sprite.draw(window);
        window.display();
    }

    return 0;
}