#include "SpriteMaker.h"

#include <iostream>

SpriteMaker::SpriteMaker(const std::string& resourcesDir)
{
    if (!enemyTexture.loadFromFile(resourcesDir + "enemies.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load Enemies texture");
    }
    enemyTexture.setSmooth(false);

    if (!playerTexture.loadFromFile(resourcesDir + "Mario & Luigi.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load Mario texture");
    }
    playerTexture.setSmooth(false);

    if (!inanimateObjectTexture.loadFromFile(resourcesDir +
                                             "inanimate objects.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load objects texture");
    }
    inanimateObjectTexture.setSmooth(false);
}

std::unique_ptr<SpriteMaker> gSpriteMaker = nullptr;

void initializeSpriteMaker(const std::string& resourceDir)
{
    gSpriteMaker = std::make_unique<SpriteMaker>(resourceDir);
}

std::unique_ptr<SpriteMaker>& getSpriteMaker()
{
    if (!gSpriteMaker)
        throw std::runtime_error("SpriteMaker was never initialized");

    return gSpriteMaker;
};
