#include "Goomba.h"
#include "AnimationBuilder.h"
#include "Timer.h"
#include "Text.h"

Goomba::Goomba(const sf::Texture& texture, const sf::Vector2f& position) :
    Entity(texture,
           16,
           16,
           Hitbox({8, 5}, {4, 7}),
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

    if (isMario(collision.entity->getType()) &&
        collision.side == EntitySide::TOP) {
        getPoints()->addPoints(100);
        terminate();
    }
    else
    {
        if (collision.side == EntitySide::BOTTOM)
        {
            clampY(hitbox.getBottom(), collision.yIntersection);
            const auto currentVelocity = getVelocity();
            setVelocity(sf::Vector2f(currentVelocity.x, 0));
        }
        else if (collision.side == EntitySide::RIGHT)
        {
            clampX(hitbox.getRight(), collision.xIntersection);
            setVelocity(sf::Vector2f(0, getVelocity().y));
        }
        else if (collision.side == EntitySide::LEFT)
        {
            clampX(hitbox.getLeft(), collision.xIntersection);
            setVelocity(sf::Vector2f(0, getVelocity().y));
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
