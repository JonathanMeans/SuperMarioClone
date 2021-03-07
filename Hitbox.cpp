#include "Hitbox.h"
#include "Entity.h"
#include "SFML/Graphics.hpp"

Hitbox::Hitbox(sf::Vector2f size, sf::Vector2f upperLeftOffset) :
    mSize(size),
    mUpperLeftOffset(upperLeftOffset)
{
}

Hitbox& Hitbox::operator=(const Hitbox& other)
{
    if (this == &other)
        return *this;
    mUpperLeftOffset = other.mUpperLeftOffset;
    mSize = other.mSize;
    return *this;
}

bool Hitbox::collidesWith(const sf::Vector2f& thisPosition,
                          const Hitbox& other,
                          const sf::Vector2f& otherPosition) const
{
    const auto thisLeft = this->getLeft(thisPosition);
    const auto thisRight = this->getRight(thisPosition);
    const auto thisTop = this->getTop(thisPosition);
    const auto thisBottom = this->getBottom(thisPosition);

    const auto otherRight = other.getRight(otherPosition);
    const auto otherLeft = other.getLeft(otherPosition);
    const auto otherTop = other.getTop(otherPosition);
    const auto otherBottom = other.getBottom(otherPosition);

    return (thisLeft < otherRight && thisRight > otherLeft &&
            thisTop < otherBottom && thisBottom > otherTop);
}

Hitbox::Hitbox(const Hitbox& copy) = default;

void Hitbox::invalidate()
{
    mSize = {};
    mUpperLeftOffset = {-10000.f, -10000.f};
}

float Hitbox::getBottom(const sf::Vector2f& entityPosition) const
{
    return getTop(entityPosition) + mSize.y;
}

float Hitbox::getTop(const sf::Vector2f& entityPosition) const
{
    return entityPosition.y + mUpperLeftOffset.y;
}

float Hitbox::getLeft(const sf::Vector2f& entityPosition) const
{
    return entityPosition.x + mUpperLeftOffset.x;
}

float Hitbox::getRight(const sf::Vector2f& entityPosition) const
{
    return getLeft(entityPosition) + mSize.x;
}

void Hitbox::getCorner(const EntityCorner& corner,
                       const sf::Vector2f& entityPosition,
                       sf::Vector2f& point) const
{
    switch (corner)
    {
    case EntityCorner::UPPER_LEFT:
        point.x = getLeft(entityPosition);
        point.y = getTop(entityPosition);
        break;
    case EntityCorner::UPPER_RIGHT:
        point.x = getRight(entityPosition);
        point.y = getTop(entityPosition);
        break;
    case EntityCorner::LOWER_RIGHT:
        point.x = getRight(entityPosition);
        point.y = getBottom(entityPosition);
        break;
    case EntityCorner::LOWER_LEFT:
        point.x = getLeft(entityPosition);
        point.y = getBottom(entityPosition);
        break;
    }
}

void Hitbox::getSide(const EntitySide& side,
                     bool extendEdges,
                     const sf::Vector2f& entityPosition,
                     sf::Vector2f& p1,
                     sf::Vector2f& p2) const
{
    // The `extendEdges` argument is to deal with a corner case where we've
    // detected a collision, but one hitbox is fully inside the other,
    // so no two edges will intersect with each other.
    // If handling this case we extend the edges of the hitbox in question
    // out to "infinity" so that it can still register intersections
    // when completely contained inside another hitbox.
    switch (side)
    {
    case EntitySide::TOP:
    {
        p1.x = getLeft(entityPosition);
        p2.x = getRight(entityPosition);
        p1.y = getTop(entityPosition);
        p2.y = getTop(entityPosition);

        if (extendEdges)
        {
            p1.x -= 1000;
            p2.x += 1000;
        }
        break;
    }
    case EntitySide::RIGHT:
    {
        p1.x = getRight(entityPosition);
        p2.x = getRight(entityPosition);
        p1.y = getTop(entityPosition);
        p2.y = getBottom(entityPosition);

        if (extendEdges)
        {
            p1.y -= 1000;
            p2.y += 1000;
        }
    }
    break;
    case EntitySide ::BOTTOM:
    {
        p1.x = getLeft(entityPosition);
        p2.x = getRight(entityPosition);
        p1.y = getBottom(entityPosition);
        p2.y = getBottom(entityPosition);

        if (extendEdges)
        {
            p1.x -= 1000;
            p2.x += 1000;
        }
    }
    break;
    case EntitySide ::LEFT:
    {
        p1.x = getLeft(entityPosition);
        p2.x = getLeft(entityPosition);
        p1.y = getTop(entityPosition);
        p2.y = getBottom(entityPosition);
        if (extendEdges)
        {
            p1.y -= 1000;
            p2.y += 1000;
        }
    }
    break;
    }
}

void Hitbox::draw(sf::RenderWindow& window,
                  const sf::Vector2f& entityPosition) const
{
    sf::RectangleShape rectangle(sf::Vector2f(mSize.x, mSize.y));
    rectangle.setFillColor(sf::Color(150, 50, 250));
    rectangle.setPosition(getLeft(entityPosition), getTop(entityPosition));
    window.draw(rectangle);
}
