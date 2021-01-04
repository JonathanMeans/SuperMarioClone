#include "Goomba.h"
#include "Timer.h"

#include <utility>

namespace
{
const auto MARIO_HEIGHT = 16;
}

Goomba::Goomba(std::shared_ptr<sf::Sprite> sprite,
               const sf::Vector2f& position) :
    Entity(std::move(sprite),
           16,
           16,
           Hitbox({8, 5}, {4, 7}),
           EntityType::GOOMBA,
           position)
{
    mVelocity.x = -.5;

    // TODO: WHy does order matter? Make this less bug-prone
    deathAnimation.load(AnimationType::GOOMBA_DEATH, mActiveSprite);
    walkingAnimation.load(AnimationType::GOOMBA_WALKING, mActiveSprite);

    // sets origin of sprite to be midpoint of top edge
    const auto spriteOrigin = MARIO_HEIGHT / 2;
    mActiveSprite->setOrigin(spriteOrigin, 0);

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

    // Remove hitbox
    mHitbox = Hitbox({0.f, 0.f}, {-10000.f, -100000.f});

    getTimer().scheduleSeconds(1, [&]() { this->setCleanupFlag(); });
}
