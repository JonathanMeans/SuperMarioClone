#include "Fallable.h"

Fallable::~Fallable() {}

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
