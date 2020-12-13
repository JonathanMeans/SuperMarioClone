#include "Pipe.h"

Pipe::Pipe(std::shared_ptr<sf::Sprite> sprite) :
    Entity(std::move(sprite),
           32,
           32,
           Hitbox({32, 32}, {0, 0}),
           EntityType::PIPE)
{
    mActiveSprite->setPosition(110, 100);
    mAcceleration = {};

    defaultAnimation.load(AnimationType::PIPE, mActiveSprite);
}
