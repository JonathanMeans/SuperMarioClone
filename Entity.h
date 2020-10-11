#ifndef SUPERMARIOBROS_ENTITY_H
#define SUPERMARIOBROS_ENTITY_H

#include <cstdlib>
#include <memory>
#include "SFML/Graphics.hpp"

class Entity
{
public:
    explicit Entity(const std::shared_ptr<sf::Sprite> sprite,
                    size_t hitboxWidth,
                    size_t hitboxHeight);
    virtual ~Entity();

    size_t getBottomPosition();
    void setBottomPosition(size_t newBottomY);

    virtual size_t getY() const;
    virtual size_t getX() const;
    virtual size_t getHitboxWidth() const;
    virtual size_t getHitboxHeight() const;
    virtual size_t getHeight() const;

    virtual void setPosition(size_t x, size_t y);

    [[nodiscard]] sf::Vector2f getVelocity() const;
    [[nodiscard]] sf::Vector2f getAcceleration() const;
    void setVelocity(const sf::Vector2f& newVelocity);
    void setAcceleration(const sf::Vector2f& newAcceleration);
    void updatePosition();
    virtual bool collideWithGround(size_t groundY);
    //    virtual bool collideWithEnemy(std::vector<Entity> &enemies);
    void setMaxVelocity(size_t maxVelocity);

    const size_t GRIDBOX_SIZE = 16;

protected:
    std::shared_ptr<sf::Sprite> mActiveSprite;
    sf::Vector2f mVelocity;
    sf::Vector2f mAcceleration;
    bool mChangingDirection;

private:
    int mLookDirection;
    float mMaxVelocity;
    size_t mHitboxWidth;
    size_t mHitboxHeight;
};

#endif  // SUPERMARIOBROS_ENTITY_H