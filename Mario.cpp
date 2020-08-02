#include "Mario.h"
#include "Animation.h"

#include <iostream>
#include "SFML/Graphics.hpp"

Mario::Mario()
{
    mActiveSprite = std::make_shared<sf::Sprite>();
    mActiveSprite->setPosition(100, 100);
    walkingAnimation.load(AnimationType::WALKING, mActiveSprite);
    jumpingAnimation.load(AnimationType::JUMPING, mActiveSprite);
    standingAnimation.load(AnimationType::STANDING, mActiveSprite);
}

void Mario::draw(sf::RenderWindow& window)
{
    window.draw(*mActiveSprite);
}

void Mario::setPosition(size_t x, size_t y)
{
    walkingAnimation.setPosition(x, y);
    jumpingAnimation.setPosition(x, y);
    standingAnimation.setPosition(x, y);
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

void Mario::stopWalking()
{
    mActiveSprite = standingAnimation.processAction();;
}

void Mario::jump()
{
    mActiveSprite = jumpingAnimation.processAction();
}
