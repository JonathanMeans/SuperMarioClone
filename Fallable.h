#ifndef SUPERMARIOBROS_FALLABLE_H
#define SUPERMARIOBROS_FALLABLE_H

#include <cstdlib>
#include "SFML/Graphics.hpp"

class Fallable
{
public:
    Fallable();
    virtual ~Fallable();

    size_t getBottomPosition();
    void setBottomPosition(size_t newBottomY);

    virtual size_t getY() const = 0;
    virtual size_t getX() const = 0;
    virtual size_t getHeight() const = 0;

    virtual void setPosition(size_t x, size_t y) = 0;

    [[nodiscard]] sf::Vector2f getVelocity() const;
    [[nodiscard]] sf::Vector2f getAcceleration() const;
    void setVelocity(const sf::Vector2f& newVelocity);
    void setAcceleration(const sf::Vector2f& newAcceleration);

    void updatePosition();
    virtual bool collideWithGround(size_t groundY);
    void setMaxVelocity(size_t maxVelocity);

protected:
    sf::Vector2f mVelocity;
    sf::Vector2f mAcceleration;
    bool mChangingDirection;

private:
    int mLookDirection;
    float mMaxVelocity;
};

#endif  // SUPERMARIOBROS_FALLABLE_H
