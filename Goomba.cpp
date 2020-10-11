#include "Goomba.h"
#include <iostream>

namespace
{
const auto MARIO_HEIGHT = 16;
}

Goomba::Goomba(const std::shared_ptr<sf::Sprite> sprite) :
    Entity(sprite, 16, 16)
{
    mActiveSprite->setPosition(150, 50);

    walkingAnimation.load(AnimationType::GOOMBA_WALKING, mActiveSprite);
    const auto spriteOrigin = MARIO_HEIGHT / 2;
    mActiveSprite->setOrigin(spriteOrigin, 0);

    mActiveAnimation = &walkingAnimation;
}
