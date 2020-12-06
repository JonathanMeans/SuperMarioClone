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
               size_t spriteWidth,
               size_t spriteHeight,
               Hitbox hitbox) :
    mActiveSprite(std::move(sprite)),
    mVelocity(0, 0),
    mAcceleration(0, GRAVITY_ACCELERATION),
    mChangingDirection(false),
    mActiveAnimation(nullptr),
    mSpriteWidth(spriteWidth),
    mSpriteHeight(spriteHeight),
    mHitbox(hitbox),
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

void Entity::die()
{
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
    if (spriteBottom <= groundY)
        return false;
    while (spriteBottom > groundY)
    {
        mDeltaP.y -= 1;
        const auto currentVelocity = getVelocity();
        setVelocity(sf::Vector2f(currentVelocity.x, 0));
        spriteBottom = getBottomPosition();
    }
    return true;
}

void Entity::getHitboxSide(const EntitySide& side,
                           bool extendEdges,
                           sf::Vector2f& p1,
                           sf::Vector2f& p2) const
{
    mHitbox.getSide(side,
                    extendEdges,
                    {static_cast<float>(getX()), static_cast<float>(getY())},
                    p1,
                    p2);
}

void Entity::getHitboxCorner(const EntityCorner& corner,
                             sf::Vector2f& point) const
{
    mHitbox.getCorner(corner,
                      {static_cast<float>(getX()), static_cast<float>(getY())},
                      point);
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

    mDeltaP.x += mVelocity.x;
    mDeltaP.y += mVelocity.y;
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
    return mSpriteHeight;
}

size_t Entity::getWidth() const
{
    return mSpriteWidth;
}

void Entity::setPosition(size_t x, size_t y)
{
    mActiveSprite->setPosition(x, y);
}

void Entity::setCleanupFlag()
{
    mCleanupFlag = true;
}

bool Entity::needsCleanup()
{
    return mCleanupFlag;
}

void Entity::applyDeltaP()
{
    setPosition(getX() + mDeltaP.x, getY() + mDeltaP.y);
}
