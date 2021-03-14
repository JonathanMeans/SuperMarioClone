#include "Block.h"

Block::Block(const sf::Sprite& sprite, const sf::Vector2f& position) :
        Entity(sprite,
               16,
               16,
               Hitbox({16, 16}, {0, 0}),
               EntityType::BLOCK,
               position)
{
    mAcceleration = {};

    defaultAnimation.load(AnimationType::BLOCK, mActiveSprite);
    mActiveAnimation = &defaultAnimation;
}