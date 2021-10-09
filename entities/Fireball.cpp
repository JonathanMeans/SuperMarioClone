#include "Fireball.h"

#include <AnimationBuilder.h>
#include <Timer.h>
#include <iostream>

Fireball::Fireball(const sf::Texture& texture, const sf::Vector2f& position, int direction) :
    Entity(texture,
           8,
           8,
           Hitbox({8, 8}, {0, 0}),
           EntityType::FIREBALL,
           position)
{
    mVelocity.x = direction * 2.f;

    deathAnimation = AnimationBuilder().withOffset(114, 160).withRectSize(12,16).build(mActiveSprite);

    sf::Rect topLeftRect = sf::IntRect(96, 144, 8, 8);
    sf::Rect topRightRect = sf::IntRect(104, 144, 8, 8);
    sf::Rect bottomLeftRect = sf::IntRect(96, 152, 8, 8);
    sf::Rect bottomRightRect = sf::IntRect(104, 152, 8, 8);
    std::vector<sf::IntRect> spinningAnimation = {topLeftRect, topRightRect, bottomLeftRect, bottomRightRect};
    defaultAnimation = AnimationBuilder().withNonContiguousRect(spinningAnimation).andRepeat().build(mActiveSprite);
    mActiveAnimation = &defaultAnimation;
}

void Fireball::onCollision(const Collision& collision)
{
    EntityType entityType = collision.entity->getType();
    if (isEnemy(entityType))
    {
        terminate();
    }
    else if (isObject(entityType))
    {
        const auto hitbox = getHitbox(collision.entity->getType());
        const float yVelocityOnBounce = 5.f;
        if (collision.side == EntitySide::LEFT || collision.side == EntitySide::RIGHT)
        {
            terminate();
        }
        else if (collision.side == EntitySide::BOTTOM)
        {
            clampY(hitbox.getBottom(), collision.yIntersection);
            mVelocity.y = -yVelocityOnBounce;
        }
        else if (collision.side == EntitySide::TOP)
        {
            clampY(hitbox.getTop(), collision.yIntersection);
            mVelocity.y = yVelocityOnBounce;
        }
    }


}

void Fireball::terminate()
{
    mActiveAnimation = &deathAnimation;
    mActiveAnimation->processAction();

    mVelocity = {};
    mAcceleration = {};

    mMarioCollisionHitbox.invalidate();
    mSpriteBoundsHitbox.invalidate();

    getTimer().scheduleSeconds(0.1, [&]() { this->setCleanupFlag(); });
}
