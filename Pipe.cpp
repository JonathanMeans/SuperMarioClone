#include "Pipe.h"

Pipe::Pipe(std::shared_ptr<sf::Sprite> sprite, const sf::Vector2f& position) :
    Entity(std::move(sprite),
           32,
           32,
           Hitbox(*this, {32, 32}, {0, 0}),
           EntityType::PIPE,
           position)
{
    mAcceleration = {};

    defaultAnimation.load(AnimationType::PIPE, mActiveSprite);
}
