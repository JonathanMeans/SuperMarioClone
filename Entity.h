#ifndef SUPERMARIOBROS_ENTITY_H
#define SUPERMARIOBROS_ENTITY_H

#include <SFML/System.hpp>
#include <cstdlib>
#include <memory>
#include "Animation.h"
#include "Hitbox.h"
#include "SFML/Graphics.hpp"

class Entity
{
public:
    static const float NO_MAX_VELOCITY_VALUE;

    Entity(std::shared_ptr<sf::Sprite> sprite,
           size_t spriteWidth,
           size_t spriteHeight,
           Hitbox hitbox,
           float maxVelocity = NO_MAX_VELOCITY_VALUE);
    virtual ~Entity();

    size_t getBottomPosition();

    [[nodiscard]] virtual size_t getY() const;
    [[nodiscard]] virtual size_t getX() const;
    [[nodiscard]] size_t getWidth() const;
    [[nodiscard]] virtual size_t getHeight() const;

    virtual void setAnimationFromState();

    [[nodiscard]] sf::Vector2f getVelocity() const;
    [[nodiscard]] sf::Vector2f getAcceleration() const;
    void setVelocity(const sf::Vector2f& newVelocity);
    void setAcceleration(const sf::Vector2f& newAcceleration);
    void updatePosition();
    void applyDeltaP();
    virtual bool collideWithGround(size_t groundY);

    void updateAnimation();
    void draw(sf::RenderWindow& window);

    void getHitboxSide(const EntitySide& side,
                       bool extendEdges,
                       sf::Vector2f& p1,
                       sf::Vector2f& p2) const;
    void getHitboxCorner(const EntityCorner& corner, sf::Vector2f& point) const;

    virtual void die();

    void setCleanupFlag();
    bool needsCleanup();

    const size_t GRIDBOX_SIZE = 16;
    const size_t GRAVITY_ACCELERATION = 1;

    sf::Vector2f mDeltaP;

protected:
    virtual void setPosition(size_t x, size_t y);

    std::shared_ptr<sf::Sprite> mActiveSprite;
    sf::Vector2f mVelocity;
    sf::Vector2f mAcceleration;
    bool mChangingDirection;
    Animation* mActiveAnimation;
    size_t mSpriteWidth;
    size_t mSpriteHeight;
    Hitbox mHitbox;
    bool mCleanupFlag = false;

    // TODO: This only applies to Mario subclass, but
    // we check it up here???
    bool mInputEnabled;

private:
    int mLookDirection;
    float mMaxVelocity;
};

#endif  // SUPERMARIOBROS_ENTITY_H
