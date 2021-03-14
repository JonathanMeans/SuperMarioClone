
#ifndef SUPERMARIOBROS_HITBOX_H
#define SUPERMARIOBROS_HITBOX_H
#include "SFML/Graphics.hpp"

class Entity;

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
    Hitbox(const Hitbox& copy);

    Hitbox& operator=(const Hitbox& other);

    void setEntityPosition(const sf::Vector2f& newEntityPosition);

    void invalidate();

    [[nodiscard]] float getBottom() const;
    [[nodiscard]] float getTop() const;
    [[nodiscard]] float getLeft() const;
    [[nodiscard]] float getRight() const;

    [[nodiscard]] bool collidesWith(const Hitbox& other) const;

    void getCorner(const EntityCorner& corner, sf::Vector2f& point) const;

    void getSide(const EntitySide& side,
                 bool extendEdges,
                 sf::Vector2f& p1,
                 sf::Vector2f& p2) const;
    void draw(sf::RenderWindow& window) const;

    sf::Vector2f mSize;
    sf::Vector2f mUpperLeftOffset;
    sf::Vector2f mEntityPosition;
};

#endif  // SUPERMARIOBROS_HITBOX_H
