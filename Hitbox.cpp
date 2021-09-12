#include "Hitbox.h"

#include "SFML/Graphics.hpp"

Hitbox::Hitbox(sf::Vector2f size,
               sf::Vector2f upperLeftOffset,
               size_t entityHeight) :
    mSize(size),
    mUpperLeftOffset(upperLeftOffset),
    mEntityPosition({-1000, -1000}),
    mIsValid(true),
    mEntityHeight(entityHeight)
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
    mEntityHeight = other.mEntityHeight;
    return *this;
}

bool Hitbox::collidesWith(const Hitbox& other) const
{
    if (!mIsValid || !other.mIsValid)
    {
        return false;
    }

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

void Hitbox::invalidate()
{
    mIsValid = false;
}

void Hitbox::makeValid()
{
    mIsValid = true;
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

void Hitbox::draw(sf::RenderWindow& window) const
{
    sf::RectangleShape rectangle(sf::Vector2f(mSize.x, mSize.y));
    rectangle.setFillColor(sf::Color(150, 50, 250));
    rectangle.setPosition(getLeft(), getTop());
    window.draw(rectangle);
}
