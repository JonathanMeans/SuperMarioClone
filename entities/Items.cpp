#include "Items.h"
#include <AnimationBuilder.h>

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
        }
    }
}

void Mushroom::onCollision(const Collision& collision)
{
    const auto hitbox = getHitbox(collision.entityType);

    if (isObject(collision.entityType))
    {
        const auto currentVelocity = getVelocity();
        if (collision.side == EntitySide::BOTTOM)
        {
            clampY(hitbox.getBottom(), collision.yIntersection);
            setVelocity(sf::Vector2f(currentVelocity.x, 0));
        }
        else if (collision.side == EntitySide::LEFT)
        {
            clampX(hitbox.getLeft(), collision.xIntersection);
            setVelocity(
                    sf::Vector2f(currentVelocity.x * -1, currentVelocity.y));
        }
        else if (collision.side == EntitySide::RIGHT)
        {
            clampX(hitbox.getRight(), collision.xIntersection);
            setVelocity(
                    sf::Vector2f(currentVelocity.x * -1, currentVelocity.y));
        }
    }

    if (isMario(collision.entityType))
    {
        terminate();
    }
}

void Mushroom::terminate()
{
    this->setCleanupFlag();
}
