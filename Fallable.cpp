#include "Fallable.h"
#include <iostream>

#include "SFML/Graphics.hpp"

namespace
{
int sign(float val)
{
    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}
const float NO_MAX_VELOCITY_VALUE = -1;
}

Fallable::Fallable(const std::shared_ptr<sf::Sprite> sprite,
                   size_t hitboxWidth,
                   size_t hitboxHeight) :
    mActiveSprite(sprite),
    mVelocity(0, 0),
    mAcceleration(0, 1),
    mChangingDirection(false),
    mLookDirection(1),
    mMaxVelocity(NO_MAX_VELOCITY_VALUE),
    mHitboxWidth(hitboxWidth),
    mHitboxHeight(hitboxHeight)
{
}

Fallable::~Fallable() = default;

size_t Fallable::getBottomPosition()
{
    return getY() + getHeight();
}

sf::Vector2f Fallable::getVelocity() const
{
    return mVelocity;
}

void Fallable::setVelocity(const sf::Vector2f& newVelocity)
{
    mVelocity = newVelocity;
}

sf::Vector2f Fallable::getAcceleration() const
{
    return mAcceleration;
}

void Fallable::setAcceleration(const sf::Vector2f& acceleration)
{
    if (acceleration == this->mAcceleration)
        return;

    if (acceleration.x != 0 &&
        (sign(acceleration.x) != sign(static_cast<float>(mLookDirection))))
    {
        mChangingDirection = true;
        mLookDirection *= -1;
    }

    mAcceleration = acceleration;
}

void Fallable::setBottomPosition(size_t newBottomY)
{
    const auto newX = getX();
    const auto newY = newBottomY - getHeight();
    setPosition(newX, newY);
}

bool Fallable::collideWithGround(const size_t groundY)
{
    const auto spriteBottom = getBottomPosition();
    if (spriteBottom > groundY)
    {
        setBottomPosition(groundY);
        const auto currentVelocity = getVelocity();
        setVelocity(sf::Vector2f(currentVelocity.x, 0));
        return true;
    }
    return false;
}

void Fallable::updatePosition()
{
    mVelocity.x += mAcceleration.x;
    mVelocity.y += mAcceleration.y;

    if (mMaxVelocity != NO_MAX_VELOCITY_VALUE)
    {
        if (mVelocity.x > 0 && mVelocity.x > mMaxVelocity)
            mVelocity.x = mMaxVelocity;

        if (mVelocity.x < 0 && mVelocity.x < -mMaxVelocity)
            mVelocity.x = -mMaxVelocity;
    }

    const auto newX = getX() + mVelocity.x;
    const auto newY = getY() + mVelocity.y;
    setPosition(newX, newY);
}

void Fallable::setMaxVelocity(size_t maxVelocity)
{
    mMaxVelocity = maxVelocity;
}

size_t Fallable::getX() const
{
    return mActiveSprite->getPosition().x;
}

size_t Fallable::getY() const
{
    return mActiveSprite->getPosition().y;
}

size_t Fallable::getHeight() const
{
    return GRIDBOX_SIZE;
}

size_t Fallable::getHitboxWidth() const
{
    return mHitboxWidth;
}

size_t Fallable::getHitboxHeight() const
{
    return mHitboxHeight;
}

void Fallable::setPosition(size_t x, size_t y)
{
    mActiveSprite->setPosition(x, y);
}
