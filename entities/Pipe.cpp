#include "Pipe.h"
#include <AnimationBuilder.h>

Pipe::Pipe(const sf::Texture& texture, const sf::Vector2f& position) :
    Entity(texture, 32, 32, Hitbox({32, 32}, {0, 0}), EntityType::PIPE, position)
{
    mAcceleration = {};

    defaultAnimation =
            AnimationBuilder().withOffset(0, 129).withRectSize(32, 32).build(
                    mActiveSprite);
    mActiveAnimation = &defaultAnimation;
}
