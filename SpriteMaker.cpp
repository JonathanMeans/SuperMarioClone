#include "SpriteMaker.h"

#include <iostream>

SpriteMaker::SpriteMaker(const std::string& resourcesDir)
{

    if (!enemiesTexture.loadFromFile(resourcesDir + "enemies.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load Enemies texture");
    }
    enemiesTexture.setSmooth(false);
    goombaSprite.setTexture(enemiesTexture);

    if (!playerTexture.loadFromFile(resourcesDir + "Mario & Luigi.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load Mario texture");
    }
    playerTexture.setSmooth(false);
    marioSprite.setTexture(playerTexture);

    if (!inanimateObjectTexture.loadFromFile(resourcesDir + "inanimate objects.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load objects texture");
    }
    inanimateObjectTexture.setSmooth(false);
    pipeSprite.setTexture(inanimateObjectTexture);
    groundSprite.setTexture(inanimateObjectTexture);
    blockSprite.setTexture(inanimateObjectTexture);
}
