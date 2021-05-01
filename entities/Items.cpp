#include "Items.h"
#include <AnimationBuilder.h>

Mushroom::Mushroom(const sf::Texture& texture, const sf::Vector2f& position) :
    Entity(texture,
           16,
           16,
           Hitbox({16, 16}, {0, 0}),
           EntityType::MUSHROOM,
           position)
{
    mAcceleration = {0, GRAVITY_ACCELERATION};
    mVelocity = {2, 0};

    defaultAnimation =
            AnimationBuilder().withOffset(0, 0).withRectSize(16, 16).build(
                    mActiveSprite);
    mActiveAnimation = &defaultAnimation;
}

void Mushroom::onCollision(const Collision& collision)
{
    const auto hitbox = getHitbox(collision.entityType);

    if (isObject(collision.entityType))
    {
        if (collision.side == EntitySide::BOTTOM)
        {
            auto spriteBottom = hitbox.getBottom();
            auto newSpriteBottom = collision.yIntersection;
            const auto delta = newSpriteBottom - spriteBottom;
            addPositionDelta(0, delta);

            const auto currentVelocity = getVelocity();
            setVelocity(sf::Vector2f(currentVelocity.x, 0));
        }
    }

    int debugPoint;
    (void) debugPoint;
}
