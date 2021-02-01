#ifndef SUPERMARIOBROS_ENTITY_H
#define SUPERMARIOBROS_ENTITY_H

#include <SFML/System.hpp>
#include <cstdlib>
#include <memory>
#include "Animation.h"
#include "Hitbox.h"
#include "SFML/Graphics.hpp"

enum class EntityType
{
    GOOMBA,
    MARIO,
    PIPE
};

std::string convertSideToString(EntitySide side);
bool isEnemy(EntityType type);

struct Collision
{
    EntitySide side;
    EntityType entityType;
    long yIntersection;
};

class Entity
{
public:
    static const float NO_MAX_VELOCITY_VALUE;

    Entity(std::shared_ptr<sf::Sprite> sprite,
           size_t spriteWidth,
           size_t spriteHeight,
           Hitbox hitbox,
           EntityType type,
           const sf::Vector2f& position,
           float maxVelocity = NO_MAX_VELOCITY_VALUE);
    virtual ~Entity();

    [[nodiscard]] long getBottom() const;
    [[nodiscard]] long getTop() const;
    [[nodiscard]] long getLeft() const;
    [[nodiscard]] long getRight() const;

    [[nodiscard]] size_t getWidth() const;
    [[nodiscard]] virtual size_t getHeight() const;

    [[nodiscard]] const Hitbox& getHitbox() const;

    virtual void setAnimationFromState();

    [[nodiscard]] sf::Vector2f getVelocity() const;
    [[nodiscard]] sf::Vector2f getAcceleration() const;
    void setVelocity(const sf::Vector2f& newVelocity);
    void setAcceleration(const sf::Vector2f& newAcceleration);
    void updatePosition();
    void addPositionDelta(float deltaX, float deltaY);
    virtual bool collideWithGround(long groundY);

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

    [[nodiscard]] EntityType getType() const;

    bool collideWithEnemy(std::vector<Entity*>& enemies);

    virtual void setPosition(float x, float y);

protected:
    std::optional<Collision> detectCollision(const Entity& other) const;

    virtual void onCollision(const Collision& collision);

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
    // These functions give the midpoint of the top edge
    // Prefer getTop(), getLeft(), etc.
    [[nodiscard]] virtual long getY() const;
    [[nodiscard]] virtual long getX() const;

    [[nodiscard]] sf::Vector2f upperCenterToUpperLeft(
            const sf::Vector2f& originalPosition) const;

    int mLookDirection;
    float mMaxVelocity;
    EntityType mType;
};

#endif  // SUPERMARIOBROS_ENTITY_H
