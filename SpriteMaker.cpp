#include "SpriteMaker.h"

#include <iostream>

SpriteMaker::SpriteMaker(const std::string& resourcesDir)
{
    if (!goombaTexture.loadFromFile(resourcesDir + "enemies.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load Enemies texture");
    }
    goombaTexture.setSmooth(false);
    goombaSprite.setTexture(goombaTexture);

    if (!marioTexture.loadFromFile(resourcesDir + "Mario & Luigi.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load Mario texture");
    }
    marioTexture.setSmooth(false);
    marioSprite.setTexture(marioTexture);

    if (!pipeTexture.loadFromFile(resourcesDir + "inanimate objects.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load objects texture");
    }
    pipeTexture.setSmooth(false);
    pipeSprite.setTexture(pipeTexture);

    if (!groundTexture.loadFromFile(resourcesDir + "inanimate objects.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load objects texture");
    }
    groundTexture.setSmooth(false);
    groundSprite.setTexture(groundTexture);

    blockSprite.setTexture(groundTexture);
}
