#ifndef SUPERMARIOBROS_BLOCK_H
#define SUPERMARIOBROS_BLOCK_H

#include "Entity.h"

class Block : public Entity
{
public:
    Block(const sf::Sprite& sprite, const sf::Vector2f& position);

private:
    Animation defaultAnimation;
};

#endif  // SUPERMARIOBROS_BLOCK_H
