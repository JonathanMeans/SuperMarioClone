#include "Entity.h"
#include <iostream>
#include <utility>

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

Entity::Entity(std::shared_ptr<sf::Sprite> sprite,
               size_t hitboxWidth,
               size_t hitboxHeight) :
    mActiveSprite(std::move(sprite)),
    mVelocity(0, 0),
    mAcceleration(0, 1),
    mChangingDirection(false),
    mActiveAnimation(nullptr),
    mHitboxWidth(hitboxWidth),
    mHitboxHeight(hitboxHeight),
    mLookDirection(1),
    mMaxVelocity(NO_MAX_VELOCITY_VALUE)
{
}

Entity::~Entity() = default;

void Entity::updateAnimation()
{
    setAnimationFromState();
    mActiveAnimation->processAction();
}

void Entity::setAnimationFromState()
{
    // Do nothing
}

void Entity::draw(sf::RenderWindow& window)
{
    window.draw(*mActiveSprite);
}

size_t Entity::getBottomPosition()
{
    return getY() + getHeight() + mDeltaP.y;
}

sf::Vector2f Entity::getVelocity() const
{
    return mVelocity;
}

void Entity::setVelocity(const sf::Vector2f& newVelocity)
{
    mVelocity = newVelocity;
}

sf::Vector2f Entity::getAcceleration() const
{
    return mAcceleration;
}

void Entity::setAcceleration(const sf::Vector2f& acceleration)
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

void Entity::setBottomPosition(size_t newBottomY)
{
    // const auto newX = getX();
    const auto newY = newBottomY - getHeight();
    mDeltaP.y += static_cast<float>(newY) - getY();
    // setPosition(newX, newY);
}

bool Entity::collideWithGround(const size_t groundY)
{
    auto spriteBottom = getBottomPosition();
    if (spriteBottom <= groundY) return false;
    while (spriteBottom > groundY)
    {
        mDeltaP.y -= 1;
        const auto currentVelocity = getVelocity();
        setVelocity(sf::Vector2f(currentVelocity.x, 0));
        spriteBottom = getBottomPosition();
    }
    return true;
}

void Entity::updatePosition()
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

    // const auto newX = getX() + mVelocity.x;
    // const auto newY = getY() + mVelocity.y;
    mDeltaP.x += mVelocity.x;
    mDeltaP.y += mVelocity.y;
    // setPosition(newX, newY);
}

void Entity::setMaxVelocity(size_t maxVelocity)
{
    mMaxVelocity = maxVelocity;
}

size_t Entity::getX() const
{
    return mActiveSprite->getPosition().x + mDeltaP.x;
}

size_t Entity::getY() const
{
    return mActiveSprite->getPosition().y + mDeltaP.y;
}

size_t Entity::getHeight() const
{
    return mHitboxHeight;
}

size_t Entity::getWidth() const
{
    return mHitboxWidth;
}

void Entity::setPosition(size_t x, size_t y)
{
    mActiveSprite->setPosition(x, y);
}
