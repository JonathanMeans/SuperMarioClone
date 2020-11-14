
#ifndef SUPERMARIOBROS_HITBOX_H
#define SUPERMARIOBROS_HITBOX_H
#include "SFML/Graphics.hpp"

class Hitbox
{
    public:
        Hitbox(sf::Vector2f size, sf::Vector2f upperLeftOffset);

        sf::Vector2f mSize;
        sf::Vector2f mUpperLeftOffset;

};

#endif  // SUPERMARIOBROS_HITBOX_H
