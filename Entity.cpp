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

EntitySide oppositeSide(EntitySide side)
{
    switch (side)
    {
    case EntitySide::TOP:
        return EntitySide::BOTTOM;

    case EntitySide::BOTTOM:
        return EntitySide::TOP;

    case EntitySide::LEFT:
        return EntitySide::RIGHT;

    case EntitySide::RIGHT:
        return EntitySide::LEFT;
    }
    throw std::runtime_error("Failed to match EntitySide");
}

// Jumping allows entities to clip through other entities
// To fix this, check the left and right sides for collisions first
const std::vector<EntitySide> SIDES{EntitySide::LEFT,
                                    EntitySide::RIGHT,
                                    EntitySide::BOTTOM,
                                    EntitySide::TOP};

const std::vector<EntityCorner> CORNERS{EntityCorner::UPPER_LEFT,
                                        EntityCorner::UPPER_RIGHT,
                                        EntityCorner::LOWER_RIGHT,
                                        EntityCorner::LOWER_LEFT};
}

std::string convertSideToString(EntitySide side)
{
    switch (side)
    {
    case EntitySide::TOP:
        return "TOP";

    case EntitySide::BOTTOM:
        return "BOTTOM";

    case EntitySide::LEFT:
        return "LEFT";

    case EntitySide::RIGHT:
        return "RIGHT";
    }
    throw std::runtime_error("Failed to match EntitySide");
}

bool isEnemy(EntityType type)
{
    switch (type)
    {
    case EntityType::GOOMBA:
        return true;
    default:
        return false;
    }
}

const float Entity::NO_MAX_VELOCITY_VALUE = -1;
const float Entity::MAX_FALLING_VELOCITY = 4.5;

Entity::Entity(const sf::Texture& texture,
               size_t spriteWidth,
               size_t spriteHeight,
               const Hitbox& hitbox,
               EntityType type,
               const sf::Vector2f& position,
               float maxVelocity) :
    mActiveSprite(texture),
    mVelocity(0, 0),
    mAcceleration(0, GRAVITY_ACCELERATION),
    mChangingDirection(false),
    mActiveAnimation(nullptr),
    mSpriteWidth(spriteWidth),
    mSpriteHeight(spriteHeight),
    mMarioCollisionHitbox(hitbox),
    mSpriteBoundsHitbox(createSpriteBoundsHitbox()),
    mInputEnabled(true),
    mLookDirection(1),
    mMaxVelocity(maxVelocity),
    mType(type)
{
    mActiveSprite.setPosition(upperCenterToUpperLeft(position));

    // sets origin of sprite to be midpoint of top edge
    // So that scaling by -1 works properly
    const auto horizontalMidpoint = spriteWidth / 2;
    mActiveSprite.setOrigin(horizontalMidpoint, 0);

    updateHitboxPositions();
}

Hitbox Entity::createSpriteBoundsHitbox() const
{
    return {{static_cast<float>(mSpriteWidth),
             static_cast<float>(mSpriteHeight)},
            {0, 0}};
}

void Entity::updateHitboxPositions()
{
    mMarioCollisionHitbox.setEntityPosition({getLeft(), getTop()});
    mSpriteBoundsHitbox.setEntityPosition({getLeft(), getTop()});
}

sf::Vector2f Entity::upperCenterToUpperLeft(
        const sf::Vector2f& originalPosition) const
{
    return sf::Vector2(originalPosition.x + (mSpriteWidth / 2.f),
                       originalPosition.y);
}

Entity::~Entity() = default;

EntityType Entity::getType() const
{
    return mType;
}

const Hitbox& Entity::getHitbox(EntityType type) const
{
    switch (type)
    {
    case EntityType ::MARIO:
        return mMarioCollisionHitbox;
    default:
        return mSpriteBoundsHitbox;
    }
}

bool Entity::detectCollision(Entity& other)
{
    const auto currentPosition = sf::Vector2f(getLeft(), getTop());
    const auto originalPosition = currentPosition - this->mDeltaP;
    const auto newXPosition =
            originalPosition + sf::Vector2f{this->mDeltaP.x, 0};
    const auto newYPosition =
            originalPosition + sf::Vector2f{0, this->mDeltaP.y};

    bool collided = false;

    Hitbox xHitbox(getHitbox(other.getType()));
    xHitbox.setEntityPosition(newXPosition);
    if (xHitbox.collidesWith(other.getHitbox(mType)))

    {
        handleCollision(
                Collision{
                        mDeltaP.x > 0 ? EntitySide::RIGHT : EntitySide::LEFT,
                        other.getType(),
                        0,
                        mDeltaP.x > 0 ? other.getHitbox(mType).getLeft()
                                      : other.getHitbox(mType).getRight(),
                },
                other);
        collided = true;
    }

    Hitbox yHitbox(getHitbox(other.getType()));
    yHitbox.setEntityPosition(newYPosition);
    if (yHitbox.collidesWith(other.getHitbox(mType)))
    {
        handleCollision(
                Collision{
                        mDeltaP.y > 0 ? EntitySide::BOTTOM : EntitySide::TOP,
                        other.getType(),
                        mDeltaP.y > 0 ? other.getHitbox(mType).getTop()
                                      : other.getHitbox(mType).getBottom(),
                        0,
                },
                other);
        collided = true;
    }

    return collided;
}

void Entity::handleCollision(Collision collision, Entity& entity)
{
    onCollision(Collision{collision.side,
                          collision.entityType,
                          collision.yIntersection,
                          collision.xIntersection});
    entity.onCollision(Collision{oppositeSide(collision.side),
                                 this->getType(),
                                 collision.yIntersection,
                                 collision.xIntersection});
}

void Entity::onCollision(const Collision& collision)
{
    // do nothing
    (void)collision;
}

bool Entity::collideWithEntity(std::vector<std::unique_ptr<Entity>>& entities)
{
    bool collided = false;
    for (auto& entity : entities)
    {
        collided |= collideWithEntity(entity);
    }
    return collided;
}

bool Entity::collideWithEntity(std::unique_ptr<Entity>& entity)
{
    return detectCollision(*entity);
}

void Entity::updateAnimation()
{
    setAnimationFromState();
    mActiveAnimation->processAction();
}

void Entity::setAnimationFromState()
{
    // Do nothing
}

void Entity::draw(sf::RenderWindow& window) const
{
    window.draw(mActiveSprite);
#ifdef DRAW_HITBOX
    mMarioCollisionHitbox.draw(window);
#endif
}

float Entity::getBottom() const
{
    return getY() + getHeight();
}

float Entity::getTop() const
{
    return getY();
}

float Entity::getLeft() const
{
    const auto halfWidth = static_cast<long>(getWidth() / 2);
    return getX() - halfWidth;
}

float Entity::getRight() const
{
    const auto halfWidth = static_cast<long>(getWidth() / 2);
    return getX() + halfWidth;
}

sf::Vector2f Entity::getVelocity() const
{
    return mVelocity;
}

void Entity::setVelocity(const sf::Vector2f& newVelocity)
{
    if (mInputEnabled)
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
    if (mInputEnabled)
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
}

void Entity::addPositionDelta(float deltaX, float deltaY)
{
    setPosition(getX() + deltaX, getY() + deltaY);
    mDeltaP.x += deltaX;
    mDeltaP.y += deltaY;
}

void Entity::doInternalCalculations()
{
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

    if (mVelocity.y > MAX_FALLING_VELOCITY)
        mVelocity.y = MAX_FALLING_VELOCITY;

    addPositionDelta(mVelocity.x, mVelocity.y);
}

float Entity::getX() const
{
    return mActiveSprite.getPosition().x;
}

float Entity::getY() const
{
    return mActiveSprite.getPosition().y;
}

float Entity::getHeight() const
{
    return mSpriteHeight;
}

float Entity::getWidth() const
{
    return mSpriteWidth;
}

void Entity::setPosition(float x, float y)
{
    mActiveSprite.setPosition(x, y);
    updateHitboxPositions();
}

void Entity::setCleanupFlag()
{
    mCleanupFlag = true;
}

bool Entity::needsCleanup()
{
    return mCleanupFlag;
}
