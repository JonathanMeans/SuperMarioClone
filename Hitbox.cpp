#include "Hitbox.h"
#include "Entity.h"
#include "SFML/Graphics.hpp"

Hitbox::Hitbox(Entity& entity,
               sf::Vector2f size,
               sf::Vector2f upperLeftOffset) :
    mSize(size),
    mUpperLeftOffset(upperLeftOffset),
    mEntity(entity)
{
}

Hitbox& Hitbox::operator=(const Hitbox& other)
{
    if (this == &other)
        return *this;
    if (&mEntity != &other.mEntity)
        throw std::runtime_error("Cannot assign to hitbox of different entity");
    mUpperLeftOffset = other.mUpperLeftOffset;
    mSize = other.mSize;
    return *this;
}

void Hitbox::invalidate()
{
    mSize = {};
    mUpperLeftOffset = {-10000.f, -10000.f};
}

long Hitbox::getBottom() const
{
    return getTop() + mSize.y;
}

long Hitbox::getTop() const
{
    return mEntity.getTop() + mUpperLeftOffset.y;
}

long Hitbox::getLeft() const
{
    return mEntity.getLeft() + mUpperLeftOffset.x;
}

long Hitbox::getRight() const
{
    return getLeft() + mSize.x;
}

void Hitbox::getCorner(const EntityCorner& corner,
                       const sf::Vector2f& spritePosition,
                       sf::Vector2f& point) const
{
    point.x = spritePosition.x + mUpperLeftOffset.x;
    point.y = spritePosition.y + mUpperLeftOffset.y;
    switch (corner)
    {
    case EntityCorner::UPPER_LEFT:
        break;
    case EntityCorner::UPPER_RIGHT:
        point.x += mSize.x;
        break;
    case EntityCorner::LOWER_RIGHT:
        point.x += mSize.x;
        point.y += mSize.y;
        break;
    case EntityCorner::LOWER_LEFT:
        point.y += mSize.y;
        break;
    }
}

void Hitbox::getSide(const EntitySide& side,
                     bool extendEdges,
                     const sf::Vector2f& spritePosition,
                     sf::Vector2f& p1,
                     sf::Vector2f& p2) const
{
    // Set both points to upper left corner of hitbox
    // Then adjust per side
    p1.x = spritePosition.x + mUpperLeftOffset.x;
    p1.y = spritePosition.y + mUpperLeftOffset.y;
    p2.x = spritePosition.x + mUpperLeftOffset.x;
    p2.y = spritePosition.y + mUpperLeftOffset.y;

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
        if (!extendEdges)
            p2.x += mSize.x;
        else
        {
            p1.x -= 1000;
            p2.x += 1000;
        }
        break;
    }
    case EntitySide::RIGHT:
    {
        p1.x += mSize.x;
        p2.x += mSize.x;

        if (!extendEdges)
            p2.y += mSize.y;
        else
        {
            p1.y -= 1000;
            p2.y += 1000;
        }
    }
    break;
    case EntitySide ::BOTTOM:
    {
        p1.y += mSize.y;
        p2.y += mSize.y;

        if (!extendEdges)
            p1.x += mSize.x;
        else
        {
            p1.x -= 1000;
            p2.x += 1000;
        }
    }
    break;
    case EntitySide ::LEFT:
    {
        if (!extendEdges)
            p1.y += mSize.y;

        else
        {
            p1.y -= 1000;
            p2.y += 1000;
        }
    }
    break;
    }
}

void Hitbox::draw(const sf::Vector2f& spritePosition, sf::RenderWindow& window)
{
    sf::RectangleShape rectangle(sf::Vector2f(mSize.x, mSize.y));
    rectangle.setFillColor(sf::Color(150, 50, 250));
    rectangle.setPosition(spritePosition.x + mUpperLeftOffset.x,
                          spritePosition.y + mUpperLeftOffset.y);
    window.draw(rectangle);
}
