#include "Fireball.h"

#include <AnimationBuilder.h>

Fireball::Fireball(const sf::Texture& texture, const sf::Vector2f& position, int direction) :
    Entity(texture,
           8,
           8,
           Hitbox({8, 8}, {0, 0}),
           EntityType::FIREBALL,
           position)
{
    mAcceleration = {};
    mVelocity.x = direction * 2.f;

    sf::Rect topLeftRect = sf::IntRect(96, 144, 8, 8);
    sf::Rect topRightRect = sf::IntRect(104, 144, 8, 8);
    sf::Rect bottomLeftRect = sf::IntRect(96, 152, 8, 8);
    sf::Rect bottomRightRect = sf::IntRect(104, 152, 8, 8);
    std::vector<sf::IntRect> spinningAnimation = {topLeftRect, topRightRect, bottomLeftRect, bottomRightRect};
    defaultAnimation = AnimationBuilder().withNonContiguousRect(spinningAnimation).andRepeat().build(mActiveSprite);
    mActiveAnimation = &defaultAnimation;
}
