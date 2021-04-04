#include "Ground.h"
#include <AnimationBuilder.h>

Ground::Ground(const sf::Sprite& sprite, const sf::Vector2f& position) :
    Entity(sprite,
           16,
           16,
           Hitbox({16, 16}, {0, 0}),
           EntityType::GROUND,
           position)
{
    mAcceleration = {};

    defaultAnimation =
            AnimationBuilder().withOffset(0, 0).withRectSize(16, 16).build(
                    mActiveSprite);
    mActiveAnimation = &defaultAnimation;
}