
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
    Hitbox(sf::Vector2f size,
           sf::Vector2f upperLeftOffset,
           size_t entityHeight);

    Hitbox(const Hitbox& copy) = default;

    Hitbox& operator=(const Hitbox& other);

    void setEntityPosition(const sf::Vector2f& newEntityPosition);

    void invalidate();
    void makeValid();

    [[nodiscard]] float getBottom() const;
    [[nodiscard]] float getTop() const;
    [[nodiscard]] float getLeft() const;
    [[nodiscard]] float getRight() const;
    [[nodiscard]] float getEntityHight() const
    {
        return mEntityHeight;
    }

    [[nodiscard]] bool collidesWith(const Hitbox& other) const;

    void draw(sf::RenderWindow& window) const;

    sf::Vector2f mSize;
    sf::Vector2f mUpperLeftOffset;
    sf::Vector2f mEntityPosition;

    bool mIsValid;

    size_t mEntityHeight;
};

#endif  // SUPERMARIOBROS_HITBOX_H
