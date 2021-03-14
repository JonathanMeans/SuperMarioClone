
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

    void invalidate();

    [[nodiscard]] float getBottom(const sf::Vector2f& entityPosition) const;
    [[nodiscard]] float getTop(const sf::Vector2f& entityPosition) const;
    [[nodiscard]] float getLeft(const sf::Vector2f& entityPosition) const;
    [[nodiscard]] float getRight(const sf::Vector2f& entityPosition) const;

    [[nodiscard]] bool collidesWith(const sf::Vector2f& thisPosition,
                                    const Hitbox& other,
                                    const sf::Vector2f& otherPosition) const;

    void getCorner(const EntityCorner& corner,
                   const sf::Vector2f& entityPosition,
                   sf::Vector2f& point) const;
    void getSide(const EntitySide& side,
                 bool extendEdges,
                 const sf::Vector2f& entityPosition,
                 sf::Vector2f& p1,
                 sf::Vector2f& p2) const;
    void draw(sf::RenderWindow& window,
              const sf::Vector2f& entityPosition) const;

    sf::Vector2f mSize;
    sf::Vector2f mUpperLeftOffset;
};

#endif  // SUPERMARIOBROS_HITBOX_H
