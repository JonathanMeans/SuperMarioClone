#include "Goomba.h"
#include <iostream>

namespace
{
const auto MARIO_HEIGHT = 16;
}

Goomba::Goomba(const std::string& resourcesDir)
{
    if (!mTexture.loadFromFile(resourcesDir + "enemies.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load Enemies texture");
    }
    mTexture.setSmooth(false);

    mActiveSprite = std::make_shared<sf::Sprite>();
    mActiveSprite->setPosition(150, 50);
    mActiveSprite->setTexture(mTexture);

    walkingAnimation.load(AnimationType::GOOMBA_WALKING, mActiveSprite);
    const auto spriteOrigin = MARIO_HEIGHT / 2;
    mActiveSprite->setOrigin(spriteOrigin, 0);

    mActiveAnimation = &walkingAnimation;
}

size_t Goomba::getHeight() const
{
    return MARIO_HEIGHT;
}

void Goomba::draw(sf::RenderWindow& window)
{
    window.draw(*mActiveSprite);
}

void Goomba::updateAnimation()
{
    mActiveAnimation->processAction();
}

void Goomba::setPosition(size_t x, size_t y)
{
    mActiveSprite->setPosition(x, y);
}

size_t Goomba::getX() const
{
    return mActiveSprite->getPosition().x;
}

size_t Goomba::getY() const
{
    return mActiveSprite->getPosition().y;
}
