#include "SpriteMaker.h"
#include "Mario.h"
#include "Pipe.h"

#include <cassert>
#include <iostream>

SpriteMaker::SpriteMaker(const std::string& resourcesDir)
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
        throw std::runtime_error("Unable to load Mario texture");
    }
    marioTexture.setSmooth(false);
    marioSprite = std::make_shared<sf::Sprite>();
    marioSprite->setTexture(marioTexture);

    if (!pipeTexture.loadFromFile(resourcesDir + "inanimate objects.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load objects texture");
    }
    pipeTexture.setSmooth(false);
    pipeSprite = std::make_shared<sf::Sprite>();
    pipeSprite->setTexture(pipeTexture);
}

EntityBuilder SpriteMaker::getMario()
{
    // TODO: All builders will have a reference to the
    // **same** sprite of each type
    // We need a way to clone sprites so we can have more than one
    return EntityBuilder(new Mario(marioSprite));
}

EntityBuilder SpriteMaker::getPipe()
{
    return EntityBuilder(new Pipe(pipeSprite));
}

EntityBuilder::EntityBuilder(Entity* entity) : mEntity(entity)
{
}

EntityBuilder EntityBuilder::atPosition(float x, float y) const
{
    assert(mEntity);
    mEntity->setPosition(x, y);
    return *this;
}

Entity* EntityBuilder::build()
{
    Entity* result = mEntity;
    mEntity = nullptr;
    return result;
}
