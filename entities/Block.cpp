
#include "Block.h"
#include <AnimationBuilder.h>
#include <SpriteMaker.h>
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
    if (!isMario(collision.entityType))
        return;
    if (collision.side != EntitySide::BOTTOM)
        return;
    if (collision.entityType == EntityType::SMALL_MARIO)
    {
        this->mVelocity.y = -4;
        this->mAcceleration.y = GRAVITY_ACCELERATION;
    }
    else
    {
        this->setCleanupFlag();

        // Spawn block shards after destruction
        // Upper left
        addEntity(std::make_unique<BlockShard>(
                getSpriteMaker()->itemAndBlockTexture,
                sf::Vector2f{getLeft(), getTop()},
                sf::Vector2f(0, 0),
                sf::Vector2f(-1, -5)));

        // Upper right
        addEntity(std::make_unique<BlockShard>(
                getSpriteMaker()->itemAndBlockTexture,
                sf::Vector2f{getLeft() + 8, getTop()},
                sf::Vector2f(8, 0),
                sf::Vector2f(1, -5)));

        // Lower right
        addEntity(std::make_unique<BlockShard>(
                getSpriteMaker()->itemAndBlockTexture,
                sf::Vector2f{getLeft() + 8, getTop() + 8},
                sf::Vector2f(8, 8),
                sf::Vector2f(1, -5)));

        // Lower left
        addEntity(std::make_unique<BlockShard>(
                getSpriteMaker()->itemAndBlockTexture,
                sf::Vector2f{getLeft(), getTop() + 8},
                sf::Vector2f(0, 8),
                sf::Vector2f(-1, -5)));
    }
}

BlockShard::BlockShard(const sf::Texture& texture,
                       const sf::Vector2f& position,
                       const sf::Vector2f& fragmentOffset,
                       const sf::Vector2f& initialVelocity) :
    Entity(texture,
           8,
           8,
           Hitbox({0, 0}, {-1000, -1000}),
           EntityType::BLOCK_SHARD,
           position)

{
    mAcceleration = {0, GRAVITY_ACCELERATION};
    mVelocity = initialVelocity;
    const auto xOffset = 304 + fragmentOffset.x;
    const auto yOffset = 112 + fragmentOffset.y;
    defaultAnimation = AnimationBuilder()
                               .withOffset(xOffset, yOffset)
                               .withRectSize(8, 8)
                               .build(mActiveSprite);
    mActiveAnimation = &defaultAnimation;

    getTimer().scheduleSeconds(10, [&]() { this->setCleanupFlag(); });
}
