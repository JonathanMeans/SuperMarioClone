
#include "Block.h"
#include <AnimationBuilder.h>
#include <Timer.h>

Block::Block(const sf::Texture& texture, const sf::Vector2f& position) :
    Entity(texture,
           16,
           16,
           Hitbox({16, 16}, {0, 0}),
           EntityType::BLOCK,
           position),
    mOriginalTop(position.y)
{
    mAcceleration = {};

    defaultAnimation =
            AnimationBuilder().withOffset(16, 0).withRectSize(16, 16).build(
                    mActiveSprite);
    mActiveAnimation = &defaultAnimation;
}

void Block::doInternalCalculations()
{
    if (this->getTop() == mOriginalTop)
    {
        mAcceleration.y = 0;
        mVelocity.y = 0;
    }
}

void Block::onCollision(const Collision& collision)
{
    if (collision.entityType != EntityType::MARIO)
        return;
    if (collision.side != EntitySide::BOTTOM)
        return;

    this->mVelocity.y = -4;
    this->mAcceleration.y = GRAVITY_ACCELERATION;
}
