#include "Ground.h"

#include <AnimationBuilder.h>

Ground::Ground(const sf::Texture& texture, const sf::Vector2f& position) :
    Entity(texture,
           16,
           16,
           Hitbox({16, 16}, {0, 0}, GRIDBOX_SIZE),
           EntityType::GROUND,
           position)
{
    mAcceleration = {};

    defaultAnimation =
            AnimationBuilder().withOffset(0, 0).withRectSize(16, 16).build(
                    mActiveSprite);
    mActiveAnimation = &defaultAnimation;
}