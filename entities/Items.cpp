#include "Items.h"

#include <AnimationBuilder.h>

Fireflower::Fireflower(const sf::Texture& texture,
                       const sf::Vector2f& position,
                       float blockTop) :
    Entity(texture,
           16,
           16,
           Hitbox({16, 16}, {0, 0}),
           EntityType::FIREFLOWER,
           position),
    mBlockTop(blockTop)
{
    mAcceleration = {0, 0};
    mVelocity = {0, -0.5};
    mSpriteBoundsHitbox.invalidate();
    mMarioCollisionHitbox.invalidate();

    defaultAnimation = AnimationBuilder()
                               .withOffset(0, 32)
                               .withRectSize(16, 16)
                               .withNumRect(4)
                               .withTicsPerFrame(2)
                               .andRepeat()
                               .build(mActiveSprite);
    mActiveAnimation = &defaultAnimation;
}

void Fireflower::doInternalCalculations()
{
    if (mAcceleration.y == 0)
    {
        if (getBottom() < mBlockTop)
        {
            mAcceleration = {0, 0};
            mVelocity = {0, 0};
            mSpriteBoundsHitbox = Hitbox({16, 16}, {0, 0});
            mMarioCollisionHitbox = Hitbox({16, 16}, {0, 0});
            mSpriteBoundsHitbox.makeValid();
            mMarioCollisionHitbox.makeValid();
        }
    }
}

void Fireflower::onCollision(const Collision& collision)
{
    if (isMario(collision.entity->getType()))
        terminate();
}

void Fireflower::terminate()
{
    this->setCleanupFlag();
}

Mushroom::Mushroom(const sf::Texture& texture,
                   const sf::Vector2f& position,
                   float blockTop) :
    Entity(texture,
           16,
           16,
           Hitbox({16, 16}, {0, 0}),
           EntityType::MUSHROOM,
           position),
    mBlockTop(blockTop)
{
    mAcceleration = {0, 0};
    mVelocity = {0, -0.5};
    mSpriteBoundsHitbox.invalidate();
    mMarioCollisionHitbox.invalidate();

    defaultAnimation =
            AnimationBuilder().withOffset(0, 0).withRectSize(16, 16).build(
                    mActiveSprite);
    mActiveAnimation = &defaultAnimation;
}

void Mushroom::doInternalCalculations()
{
    if (mAcceleration.y == 0)
    {
        if (getBottom() < mBlockTop)
        {
            mAcceleration = {0, GRAVITY_ACCELERATION};
            mVelocity.x = 2;
            mSpriteBoundsHitbox = Hitbox({16, 16}, {0, 0});
            mMarioCollisionHitbox = Hitbox({16, 16}, {0, 0});
            mSpriteBoundsHitbox.makeValid();
            mMarioCollisionHitbox.makeValid();
        }
    }
}

void Mushroom::onCollision(const Collision& collision)
{
    const auto hitbox = getHitbox(collision.entity->getType());

    if (isObject(collision.entity->getType()))
    {
        const auto currentVelocity = getVelocity();
        switch (collision.side)
        {
        case EntitySide::BOTTOM:
            clampY(hitbox.getBottom(), collision.yIntersection);
            setVelocity(sf::Vector2f(currentVelocity.x, 0));
            break;
        case EntitySide::LEFT:
            clampX(hitbox.getLeft(), collision.xIntersection);
            setVelocity(
                    sf::Vector2f(currentVelocity.x * -1, currentVelocity.y));
            break;
        case EntitySide::RIGHT:
            clampX(hitbox.getRight(), collision.xIntersection);
            setVelocity(
                    sf::Vector2f(currentVelocity.x * -1, currentVelocity.y));
            break;
        case EntitySide::TOP:
            // do nothing
            break;
        }
    }

    if (isMario(collision.entity->getType()))
    {
        terminate();
    }
}

void Mushroom::terminate()
{
    this->setCleanupFlag();
}
