#include "Goomba.h"
#include "AnimationBuilder.h"
#include "Timer.h"

Goomba::Goomba(const sf::Sprite& sprite, const sf::Vector2f& position) :
    Entity(sprite, 16, 16, Hitbox({8, 5}, {4, 7}), EntityType::GOOMBA, position)
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
