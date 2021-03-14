#include "Pipe.h"
#include <AnimationBuilder.h>

Pipe::Pipe(const sf::Sprite& sprite, const sf::Vector2f& position) :
    Entity(sprite, 32, 32, Hitbox({32, 32}, {0, 0}), EntityType::PIPE, position)
{
    mAcceleration = {};

    defaultAnimation =
            AnimationBuilder().withOffset(0, 129).withRectSize(32, 32).build(
                    mActiveSprite);
    mActiveAnimation = &defaultAnimation;
}
