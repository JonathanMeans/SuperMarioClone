#ifndef SUPERMARIOBROS_ENTITY_H
#define SUPERMARIOBROS_ENTITY_H

#include <cstdlib>
#include <memory>
#include "SFML/Graphics.hpp"
#include <SFML/System.hpp>
#include "Animation.h"

class Entity
{
public:
    explicit Entity(std::shared_ptr<sf::Sprite> sprite,
                    size_t hitboxWidth,
                    size_t hitboxHeight);
    virtual ~Entity();

    size_t getBottomPosition();
    void setBottomPosition(size_t newBottomY);

    [[nodiscard]] size_t getY() const;
    [[nodiscard]] size_t getX() const;
    [[nodiscard]] size_t getHitboxWidth() const;
    [[nodiscard]] size_t getHitboxHeight() const;
    [[nodiscard]] size_t getHeight() const;

    void setPosition(size_t x, size_t y);
    virtual void setAnimationFromState();

    [[nodiscard]] sf::Vector2f getVelocity() const;
    [[nodiscard]] sf::Vector2f getAcceleration() const;
    void setVelocity(const sf::Vector2f& newVelocity);
    void setAcceleration(const sf::Vector2f& newAcceleration);
    void updatePosition();
    virtual bool collideWithGround(size_t groundY);
    //    virtual bool collideWithEnemy(std::vector<Entity> &enemies);
    void setMaxVelocity(size_t maxVelocity);

    void updateAnimation();
    void draw(sf::RenderWindow& window);

    const size_t GRIDBOX_SIZE = 16;

protected:
    std::shared_ptr<sf::Sprite> mActiveSprite;
    sf::Vector2f mVelocity;
    sf::Vector2f mAcceleration;
    bool mChangingDirection;
    Animation* mActiveAnimation;
    size_t mHitboxWidth;
    size_t mHitboxHeight;

private:
    int mLookDirection;
    float mMaxVelocity;
};

#endif  // SUPERMARIOBROS_ENTITY_H
