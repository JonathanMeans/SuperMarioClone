#ifndef SUPERMARIOBROS_ENTITY_H
#define SUPERMARIOBROS_ENTITY_H

#include <SFML/System.hpp>
#include <cstdlib>
#include <memory>
#include "Animation.h"
#include "SFML/Graphics.hpp"

class Entity
{
public:
    explicit Entity(std::shared_ptr<sf::Sprite> sprite,
                    size_t hitboxWidth,
                    size_t hitboxHeight,
                    size_t spriteWidth,
                    size_t spriteHeight,
                    sf::Vector2f hitboxULCornerOffset);
    virtual ~Entity();

    size_t getBottomPosition();
    void setBottomPosition(size_t newBottomY);

    [[nodiscard]] virtual size_t getY() const;
    [[nodiscard]] virtual size_t getX() const;
    [[nodiscard]] size_t getWidth() const;
    [[nodiscard]] virtual size_t getHeight() const;

    virtual void setPosition(size_t x, size_t y);
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

    void getHitboxSide(int side, sf::Vector2f& p1, sf::Vector2f& p2) const;
    void getCorner(int corner, sf::Vector2f& point) const;

    const size_t GRIDBOX_SIZE = 16;

    sf::Vector2f mDeltaP;

protected:
    std::shared_ptr<sf::Sprite> mActiveSprite;
    sf::Vector2f mVelocity;
    sf::Vector2f mAcceleration;
    bool mChangingDirection;
    Animation* mActiveAnimation;
    size_t mHitboxWidth;
    size_t mHitboxHeight;
    size_t mSpriteWidth;
    size_t mSpriteHeight;
    sf::Vector2f mHitboxULCornerOffset;

private:
    int mLookDirection;
    float mMaxVelocity;
};

#endif  // SUPERMARIOBROS_ENTITY_H
