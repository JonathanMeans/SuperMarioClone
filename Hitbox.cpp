#include "Hitbox.h"
#include "SFML/Graphics.hpp"

Hitbox::Hitbox(sf::Vector2f size, sf::Vector2f upperLeftOffset) :
    mSize(size),
    mUpperLeftOffset(upperLeftOffset),
    mEntityPosition({-1000, -1000})
{
}

void Hitbox::setEntityPosition(const sf::Vector2f& newEntityPosition)
{
    mEntityPosition = newEntityPosition;
}

Hitbox& Hitbox::operator=(const Hitbox& other)
{
    if (this == &other)
        return *this;
    mUpperLeftOffset = other.mUpperLeftOffset;
    mSize = other.mSize;
    return *this;
}

bool Hitbox::collidesWith(const Hitbox& other) const
{
    const auto thisLeft = this->getLeft();
    const auto thisRight = this->getRight();
    const auto thisTop = this->getTop();
    const auto thisBottom = this->getBottom();

    const auto otherRight = other.getRight();
    const auto otherLeft = other.getLeft();
    const auto otherTop = other.getTop();
    const auto otherBottom = other.getBottom();

    return (thisLeft < otherRight && thisRight > otherLeft &&
            thisTop < otherBottom && thisBottom > otherTop);
}

Hitbox::Hitbox(const Hitbox& copy) = default;

void Hitbox::invalidate()
{
    mSize = {};
    mUpperLeftOffset = {-10000.f, -10000.f};
}

float Hitbox::getBottom() const
{
    return getTop() + mSize.y;
}

float Hitbox::getTop() const
{
    return mEntityPosition.y + mUpperLeftOffset.y;
}

float Hitbox::getLeft() const
{
    return mEntityPosition.x + mUpperLeftOffset.x;
}

float Hitbox::getRight() const
{
    return getLeft() + mSize.x;
}

void Hitbox::getCorner(const EntityCorner& corner, sf::Vector2f& point) const
{
    switch (corner)
    {
    case EntityCorner::UPPER_LEFT:
        point.x = getLeft();
        point.y = getTop();
        break;
    case EntityCorner::UPPER_RIGHT:
        point.x = getRight();
        point.y = getTop();
        break;
    case EntityCorner::LOWER_RIGHT:
        point.x = getRight();
        point.y = getBottom();
        break;
    case EntityCorner::LOWER_LEFT:
        point.x = getLeft();
        point.y = getBottom();
        break;
    }
}

void Hitbox::getSide(const EntitySide& side,
                     bool extendEdges,
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
        p1.x = getLeft();
        p2.x = getRight();
        p1.y = getTop();
        p2.y = getTop();

        if (extendEdges)
        {
            p1.x -= 1000;
            p2.x += 1000;
        }
        break;
    }
    case EntitySide::RIGHT:
    {
        p1.x = getRight();
        p2.x = getRight();
        p1.y = getTop();
        p2.y = getBottom();

        if (extendEdges)
        {
            p1.y -= 1000;
            p2.y += 1000;
        }
    }
    break;
    case EntitySide ::BOTTOM:
    {
        p1.x = getLeft();
        p2.x = getRight();
        p1.y = getBottom();
        p2.y = getBottom();

        if (extendEdges)
        {
            p1.x -= 1000;
            p2.x += 1000;
        }
    }
    break;
    case EntitySide ::LEFT:
    {
        p1.x = getLeft();
        p2.x = getLeft();
        p1.y = getTop();
        p2.y = getBottom();
        if (extendEdges)
        {
            p1.y -= 1000;
            p2.y += 1000;
        }
    }
    break;
    }
}

void Hitbox::draw(sf::RenderWindow& window) const
{
    sf::RectangleShape rectangle(sf::Vector2f(mSize.x, mSize.y));
    rectangle.setFillColor(sf::Color(150, 50, 250));
    rectangle.setPosition(getLeft(), getTop());
    window.draw(rectangle);
}
