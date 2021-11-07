#include "Goomba.h"

#include "AnimationBuilder.h"
#include "Event.h"
#include "Timer.h"

Goomba::Goomba(const sf::Texture& texture, const sf::Vector2f& position) :
    Entity(texture,
           16,
           16,
           Hitbox(sf::Vector2f(8, 5), sf::Vector2f(4, 7)),
           EntityType::GOOMBA,
           position)
{
    mVelocity.x = -.5;

    // TODO: WHy does order matter? Make this less bug-prone
    deathAnimation =
            AnimationBuilder().withOffset(32, 16).withRectSize(16, 16).build(
                    mActiveSprite);
    walkingAnimation = AnimationBuilder()
                               .withOffset(0, 16)
                               .withRectSize(16, 16)
                               .withNumRect(2)
                               .withTicsPerFrame(4)
                               .andRepeat()
                               .build(mActiveSprite);

    mActiveAnimation = &walkingAnimation;
}

void Goomba::onCollision(const Collision& collision)
{
    const auto hitbox = getHitbox(collision.entity->getType());

    EntityType entityType = collision.entity->getType();
    if ((isMario(entityType) &&
        collision.side == EntitySide::TOP) || entityType == EntityType::FIREBALL)
    {
        dispatchEvent(Event::constructPointsEarned({getTop(), getLeft()}, 100));
        terminate();
    }
    else
    {
        if (isObject(collision.entity->getType()))
        {
            if (collision.side == EntitySide::BOTTOM)
            {
                clampY(hitbox.getBottom(), collision.yIntersection);
            }
            else if (collision.side == EntitySide::RIGHT)
            {
                clampX(hitbox.getRight(), collision.xIntersection);
            }
            else if (collision.side == EntitySide::LEFT)
            {
                clampX(hitbox.getLeft(), collision.xIntersection);
            }
        }
    }
}

void Goomba::terminate()
{
    mActiveAnimation = &deathAnimation;
    mActiveAnimation->processAction();

    mVelocity = {};
    mAcceleration = {};

    mMarioCollisionHitbox.invalidate();
    mSpriteBoundsHitbox.invalidate();

    getTimer().scheduleSeconds(1, [&]() { this->setCleanupFlag(); });
}
