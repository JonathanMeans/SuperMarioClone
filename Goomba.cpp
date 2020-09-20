#include "Goomba.h"
#include <iostream>

namespace
{
const auto MARIO_HEIGHT = 16;
}

Goomba::Goomba(const std::string& resourcesDir)
{
    if (!mTexture.loadFromFile(resourcesDir + "enemies.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load Enemies texture");
    }
    mTexture.setSmooth(false);

    mActiveSprite = std::make_shared<sf::Sprite>();
    mActiveSprite->setPosition(150, 50);
    mActiveSprite->setTexture(mTexture);

    walkingAnimation.load(AnimationType::GOOMBA_WALKING, mActiveSprite);
    const auto spriteOrigin = MARIO_HEIGHT / 2;
    mActiveSprite->setOrigin(spriteOrigin, 0);

    mActiveAnimation = &walkingAnimation;
}

void Goomba::draw(sf::RenderWindow& window)
{
    window.draw(*mActiveSprite);
}

void Goomba::updateAnimation()
{
    mActiveAnimation->processAction();
}
