#include "Block.h"
#include <AnimationBuilder.h>
#include <SpriteMaker.h>
#include <Timer.h>
#include <cassert>
#include "Event.h"
#include "Items.h"
#include "Mario.h"

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
    if (!isMario(collision.entity->getType()))
        return;
    if (collision.side != EntitySide::BOTTOM)
        return;
    if (collision.entity->getType() == EntityType::SMALL_MARIO)
    {
        bumpUp();
    }
    else
    {
        this->setCleanupFlag();
        dispatchEvent(Event::constructBlockShattered({getLeft(), getTop()}));
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
    if (!isMario(collision.entity->getType()))
        return;
    if (collision.side != EntitySide::BOTTOM)
        return;
    if (mActiveAnimation == &noItemAnimation)
        return;

    bumpUp();

    auto* mario = reinterpret_cast<Mario*>(collision.entity);
    assert(mario != nullptr);

    if (mario->getForm() == MarioForm::SMALL_MARIO)
        dispatchEvent(Event::constructItemSpawned(EntityType::MUSHROOM,
                                                  sf::Vector2f(getLeft(),
                                                               getTop() - 5),
                                                  getTop()));
    else
        dispatchEvent(Event::constructItemSpawned(EntityType::FIREFLOWER,
                                                  sf::Vector2f(getLeft(),
                                                               getTop() - 5),
                                                  getTop()));
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
