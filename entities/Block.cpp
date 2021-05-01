
#include "Block.h"
#include <AnimationBuilder.h>
#include <SpriteMaker.h>
#include <Timer.h>
#include "Items.h"

Block::Block(const sf::Texture& texture, const sf::Vector2f& position) :
    Entity(texture,
           16,
           16,
           Hitbox({16, 16}, {0, 0}),
           EntityType::BLOCK,
           position),
    mOriginalTop(position.y)
{
}

void Block::doInternalCalculations()
{
    if (this->getTop() == mOriginalTop)
    {
        mAcceleration.y = 0;
        mVelocity.y = 0;
    }
}

BreakableBlock::BreakableBlock(const sf::Texture& texture,
                               const sf::Vector2f& position) :
    Block(texture, position)
{
    mAcceleration = {};

    defaultAnimation =
            AnimationBuilder().withOffset(16, 0).withRectSize(16, 16).build(
                    mActiveSprite);
    mActiveAnimation = &defaultAnimation;
}

void BreakableBlock::onCollision(const Collision& collision)
{
    if (!isMario(collision.entityType))
        return;
    if (collision.side != EntitySide::BOTTOM)
        return;
    if (collision.entityType == EntityType::SMALL_MARIO)
    {
        bumpUp();
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

ItemBlock::ItemBlock(const sf::Texture& texture, const sf::Vector2f& position) :
    Block(texture, position)
{
    mAcceleration = {};

    hasItemAnimation = AnimationBuilder()
                               .withOffset(240, 0)
                               .withRectSize(16, 16)
                               .withNumRect(3)
                               .withTicsPerFrame(2)
                               .andRepeat()
                               .build(mActiveSprite);
    noItemAnimation =
            AnimationBuilder().withOffset(288, 0).withRectSize(16, 16).build(
                    mActiveSprite);

    mActiveAnimation = &hasItemAnimation;
}

void ItemBlock::onCollision(const Collision& collision)
{
    if (!isMario(collision.entityType))
        return;
    if (collision.side != EntitySide::BOTTOM)
        return;
    if (mActiveAnimation == &noItemAnimation)
        return;

    bumpUp();
    addEntity(
            std::make_unique<Mushroom>(getSpriteMaker()->itemAndObjectTexture,
                                       sf::Vector2f(getLeft(), getTop() - 16)));

    mActiveAnimation = &noItemAnimation;
}

void Block::bumpUp()
{
    mVelocity.y = -4;
    mAcceleration.y = GRAVITY_ACCELERATION;
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
