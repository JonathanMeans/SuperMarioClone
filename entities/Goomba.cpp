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
    else
    {
        if (collision.side == EntitySide::BOTTOM)
        {
            auto spriteBottom = mHitbox.getBottom();
            auto newSpriteBottom = collision.yIntersection;
            const auto delta = newSpriteBottom - spriteBottom;
            addPositionDelta(0, delta);

            const auto currentVelocity = getVelocity();
            setVelocity(sf::Vector2f(currentVelocity.x, 0));
        }
        else if (collision.side == EntitySide::RIGHT)
        {
            auto spriteRight = mHitbox.getRight();
            auto newSpriteRight = collision.xIntersection;
            const auto delta = newSpriteRight - spriteRight;
            addPositionDelta(delta, 0);
            setVelocity(sf::Vector2f(0, getVelocity().y));
        }
        else if (collision.side == EntitySide::LEFT)
        {
            auto spriteLeft = mHitbox.getLeft();
            auto newSpriteLeft = collision.xIntersection;
            const auto delta = newSpriteLeft - spriteLeft;
            addPositionDelta(delta, 0);
            setVelocity(sf::Vector2f(0, getVelocity().y));
        }
    }
}

void Goomba::die()
{
    mActiveAnimation = &deathAnimation;
    mActiveAnimation->processAction();
    mVelocity.x = 0;

    mHitbox.invalidate();

    getTimer().scheduleSeconds(1, [&]() { this->setCleanupFlag(); });
}
