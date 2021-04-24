#ifndef SUPERMARIOBROS_BLOCK_H
#define SUPERMARIOBROS_BLOCK_H

#include "Entity.h"
class Block : public Entity
{
public:
    Block(const sf::Texture& texture, const sf::Vector2f& position);

protected:
    void onCollision(const Collision& collision) override;

    void doInternalCalculations() override;

private:
    const float mOriginalTop;  // Record initial position so we can detect when
                               // "bump" is over

    Animation defaultAnimation;
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
