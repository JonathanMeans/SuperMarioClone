#include "InvisibleWall.h"

InvisibleWall::InvisibleWall(const sf::Texture& texture,
                             const sf::Vector2f& position) :
    Entity(texture,
           16,
           9999,
           Hitbox({16, 9999}, {0, 0}),
           EntityType::INVISIBLE_WALL,
           position)
{
    mAcceleration = {0, 0};
}

void InvisibleWall::draw(sf::RenderWindow&)
{
}
