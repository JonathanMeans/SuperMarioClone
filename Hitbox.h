
#ifndef SUPERMARIOBROS_HITBOX_H
#define SUPERMARIOBROS_HITBOX_H
#include "SFML/Graphics.hpp"

enum class EntitySide
{
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

enum class EntityCorner
{
    UPPER_LEFT,
    UPPER_RIGHT,
    LOWER_RIGHT,
    LOWER_LEFT
};

class Hitbox
{
public:
    Hitbox(sf::Vector2f size, sf::Vector2f upperLeftOffset);
    void getCorner(const EntityCorner& corner,
                   const sf::Vector2f& spritePosition,
                   sf::Vector2f& point) const;
    void getSide(const EntitySide& side,
                 bool extendEdges,
                 const sf::Vector2f& spritePosition,
                 sf::Vector2f& p1,
                 sf::Vector2f& p2) const;

    sf::Vector2f mSize;
    sf::Vector2f mUpperLeftOffset;
};

#endif  // SUPERMARIOBROS_HITBOX_H
