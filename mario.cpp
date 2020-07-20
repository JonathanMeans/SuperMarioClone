#include "mario.h"

#include <iostream>
#include "SFML/Graphics.hpp"

mario::mario()
{
    if (!mTexture.loadFromFile("../resources/Mario & Luigi.png", sf::IntRect(80, 34, 16,  16)))
    {
        std::cerr << "Error Loading Texture";
    }
    sprite.setTexture(mTexture);

}

void mario::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}