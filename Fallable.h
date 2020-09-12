#ifndef SUPERMARIOBROS_FALLABLE_H
#define SUPERMARIOBROS_FALLABLE_H

#include <cstdlib>
#include "SFML/Graphics.hpp"

class Fallable
{
public:
    virtual ~Fallable();

    size_t getBottomPosition();
    void setBottomPosition(size_t newBottomY);

    virtual size_t getY() const = 0;
    virtual size_t getX() const = 0;
    virtual size_t getHeight() const = 0;
    virtual sf::Vector2f getVelocity() const = 0;
    virtual void setVelocity(const sf::Vector2f& newVelocity) = 0;
    virtual void setPosition(size_t x, size_t y) = 0;
    virtual bool collideWithGround(const size_t groundY);


};

#endif  // SUPERMARIOBROS_FALLABLE_H
