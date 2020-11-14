#include "Hitbox.h"
#include "SFML/Graphics.hpp"


Hitbox::Hitbox(sf::Vector2f size, sf::Vector2f upperLeftOffset) :
    mSize(size),
    mUpperLeftOffset(upperLeftOffset)
{
}

