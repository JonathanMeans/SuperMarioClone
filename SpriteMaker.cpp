#include "SpriteMaker.h"

#include <iostream>

SpriteMaker::SpriteMaker(const std::string &resourcesDir)
{
    if (!goombaTexture.loadFromFile(resourcesDir + "enemies.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load Enemies texture");
    }
    goombaTexture.setSmooth(false);
    goombaSprite = std::make_shared<sf::Sprite>();
    goombaSprite->setTexture(goombaTexture);

    if (!marioTexture.loadFromFile(resourcesDir + "Mario & Luigi.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load Enemies texture");
    }
    marioTexture.setSmooth(false);
    marioSprite = std::make_shared<sf::Sprite>();
    marioSprite->setTexture(marioTexture);
}


