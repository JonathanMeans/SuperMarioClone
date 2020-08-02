#include "Mario.h"
#include "Animation.h"

#include <iostream>
#include <memory>
#include "SFML/Graphics.hpp"

Mario::Mario()
{
    if (!mTexture.loadFromFile("../resources/Mario & Luigi.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load Mario texture");
    }
    mTexture.setSmooth(false);

    mActiveSprite = std::make_shared<sf::Sprite>();
    mActiveSprite->setPosition(100, 100);
    mActiveSprite->setTexture(mTexture);

    walkingAnimation.load(AnimationType::WALKING, mActiveSprite);
    jumpingAnimation.load(AnimationType::JUMPING, mActiveSprite);
    standingAnimation.load(AnimationType::STANDING, mActiveSprite);

    bigWalkingAnimation.load(AnimationType::BIG_WALKING, mActiveSprite);
}

void Mario::draw(sf::RenderWindow& window)
{
    window.draw(*mActiveSprite);
}

void Mario::setPosition(size_t x, size_t y)
{
    mActiveSprite->setPosition(x, y);
}

size_t Mario::getX() const
{
    return mActiveSprite->getPosition().x;
}

size_t Mario::getY() const
{
    return mActiveSprite->getPosition().y;
}

void Mario::walk()
{
    mActiveSprite = walkingAnimation.processAction();
}

void Mario::grow()
{
    mActiveSprite = bigWalkingAnimation.processAction();
}

void Mario::stopWalking()
{
    mActiveSprite = standingAnimation.processAction();
}

void Mario::jump()
{
    mActiveSprite = jumpingAnimation.processAction();
}
