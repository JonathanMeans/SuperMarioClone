#include "Goomba.h"
#include "Timer.h"

Goomba::Goomba(const sf::Sprite& sprite, const sf::Vector2f& position) :
    Entity(sprite,
           16,
           16,
           Hitbox(*this, {8, 5}, {4, 7}),
           EntityType::GOOMBA,
           position)
{
    mVelocity.x = -.5;

    // TODO: WHy does order matter? Make this less bug-prone
    deathAnimation.load(AnimationType::GOOMBA_DEATH, mActiveSprite);
    walkingAnimation.load(AnimationType::GOOMBA_WALKING, mActiveSprite);
    mActiveAnimation = &walkingAnimation;
}

void Goomba::onCollision(const Collision& collision)
{
    if (collision.entityType == EntityType::MARIO &&
        collision.side == EntitySide::TOP)
        die();
}

void Goomba::die()
{
    mActiveAnimation = &deathAnimation;
    mActiveAnimation->processAction();
    mVelocity.x = 0;

    mHitbox.invalidate();

    getTimer().scheduleSeconds(1, [&]() { this->setCleanupFlag(); });
}
