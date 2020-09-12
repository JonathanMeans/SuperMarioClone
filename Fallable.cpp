#include "Fallable.h"

#include "SFML/Graphics.hpp"

Fallable::~Fallable()
{
}

size_t Fallable::getBottomPosition()
{
    return getY() + getHeight();
}

void Fallable::setBottomPosition(size_t newBottomY)
{
    const auto newX = getX();
    const auto newY = newBottomY - getHeight();
    setPosition(newX, newY);
}

bool Fallable::collideWithGround(const size_t groundY)
{
    const auto spriteBottom = getBottomPosition();
    if (spriteBottom > groundY)
    {
        setBottomPosition(groundY);
        const auto currentVelocity = getVelocity();
        setVelocity(sf::Vector2f(currentVelocity.x, 0));
        return true;
    }
    return false;
}