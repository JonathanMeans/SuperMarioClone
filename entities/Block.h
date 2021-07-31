#ifndef SUPERMARIOBROS_BLOCK_H
#define SUPERMARIOBROS_BLOCK_H

#include "Entity.h"

class Block : public Entity
{
public:
    Block(const sf::Texture& texture, const sf::Vector2f& position);

protected:
    void doInternalCalculations() override;

    void bumpUp();

    const float
            mOriginalBottom;  // Record initial position so we can detect when
    // "bump" is over
};

class BreakableBlock : public Block
{
public:
    BreakableBlock(const sf::Texture& texture, const sf::Vector2f& position);

protected:
    void onCollision(const Collision& collision) override;

private:
    Animation defaultAnimation;
};

class ItemBlock : public Block
{
public:
    ItemBlock(const sf::Texture& texture, const sf::Vector2f& position);

protected:
    void onCollision(const Collision& collision) override;

private:
    Animation hasItemAnimation;
    Animation noItemAnimation;
};

class BlockShard : public Entity
{
public:
    BlockShard(const sf::Texture& texture,
               const sf::Vector2f& position,
               const sf::Vector2f& fragmentOffset,
               const sf::Vector2f& initialVelocity);

    Animation defaultAnimation;
};

#endif  // SUPERMARIOBROS_BLOCK_H
