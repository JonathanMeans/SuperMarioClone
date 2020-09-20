#include "Fallable.h"
#include <iostream>

#include "SFML/Graphics.hpp"

Fallable::Fallable() : mMaxVelocity(-1)
{
}

Fallable::~Fallable() = default;

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

void Fallable::updatePosition()
{
    auto velocity = getVelocity();
    velocity.x += getAcceleration().x;
    velocity.y += getAcceleration().y;

    if (mMaxVelocity != static_cast<size_t>(-1))
    {
        if (velocity.x > 0 && velocity.x > mMaxVelocity)
            velocity.x = mMaxVelocity;

        if (velocity.x < 0 && velocity.x < -mMaxVelocity)
            velocity.x = -mMaxVelocity;
    }

    setVelocity(velocity);

    const auto newX = getX() + velocity.x;
    const auto newY = getY() + velocity.y;
    setPosition(newX, newY);
}

void Fallable::setMaxVelocity(size_t maxVelocity)
{
    mMaxVelocity = maxVelocity;
}