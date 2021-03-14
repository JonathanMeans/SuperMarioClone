#include "Pipe.h"

Pipe::Pipe(const sf::Sprite& sprite, const sf::Vector2f& position) :
    Entity(sprite,
           32,
           32,
           Hitbox({32, 32}, {0, 0}),
           EntityType::PIPE,
           position)
{
    mAcceleration = {};

    defaultAnimation.load(AnimationType::PIPE, mActiveSprite);
    mActiveAnimation = &defaultAnimation;
}
