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
    SMALL_MARIO,
    BIG_MARIO,
    PIPE,
    GROUND,
    BLOCK,
    BLOCK_SHARD,
    MUSHROOM,
};

std::string convertSideToString(EntitySide side);
bool isEnemy(EntityType type);
bool isMario(EntityType entityType);
bool isObject(EntityType entityType);

struct Collision
{
    EntitySide side;
    EntityType entityType;
    float yIntersection;
    float xIntersection;
};

class Entity
{
public:
    static const float NO_MAX_VELOCITY_VALUE;
    static const float MAX_FALLING_VELOCITY;

    Entity(const sf::Texture& texture,
           size_t spriteWidth,
           size_t spriteHeight,
           const Hitbox& hitbox,
           EntityType type,
           const sf::Vector2f& position,
           float maxVelocity = NO_MAX_VELOCITY_VALUE);
    virtual ~Entity();

    [[nodiscard]] float getBottom() const;
    [[nodiscard]] float getTop() const;
    [[nodiscard]] float getLeft() const;
    [[nodiscard]] float getRight() const;

    [[nodiscard]] float getWidth() const;
    [[nodiscard]] virtual float getHeight() const;

    virtual void setAnimationFromState();

    [[nodiscard]] sf::Vector2f getVelocity() const;
    [[nodiscard]] sf::Vector2f getAcceleration() const;
    void setVelocity(const sf::Vector2f& newVelocity);
    void setAcceleration(const sf::Vector2f& newAcceleration);
    void updatePosition();
    virtual void doInternalCalculations();
    void addPositionDelta(float deltaX, float deltaY);

    void updateAnimation();
    void draw(sf::RenderWindow& window) const;

    virtual void terminate();

    void setCleanupFlag();
    bool needsCleanup();

    const size_t GRIDBOX_SIZE = 16;
    const float GRAVITY_ACCELERATION = 1;

    sf::Vector2f mDeltaP;

    [[nodiscard]] virtual EntityType getType() const;

    bool collideWithEntity(std::vector<std::unique_ptr<Entity>>& entities);
    bool collideWithEntity(std::unique_ptr<Entity>& entity);

    virtual void setPosition(float x, float y);

protected:
    bool detectCollision(Entity& other);

    virtual void onCollision(const Collision& collision);

    void clampX(float spriteX, float newSpriteX);

    void clampY(float spriteY, float newSpriteY);

    void handleCollision(Collision collision, Entity& entity);

    virtual const Hitbox& getHitbox(EntityType type) const;

    Hitbox createSpriteBoundsHitbox() const;

    void updateHitboxPositions();

    sf::Sprite mActiveSprite;
    sf::Vector2f mVelocity;
    sf::Vector2f mAcceleration;
    bool mChangingDirection;
    Animation* mActiveAnimation;
    size_t mSpriteWidth;
    size_t mSpriteHeight;

    // Current theory is that there are two hitboxes
    // mMarioCollisionHitbox is used to detect collision for Mario against
    // an enemy. It is typically smaller to make the game feel more "fair"
    // The other is used for all (??) other collisions.
    Hitbox mMarioCollisionHitbox;
    Hitbox mSpriteBoundsHitbox;

    bool mCleanupFlag = false;

    // TODO: This only applies to Mario subclass, but
    // we check it up here???
    bool mInputEnabled;

private:
    // These functions give the midpoint of the top edge
    // Prefer getTop(), getLeft(), etc.
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getX() const;

    [[nodiscard]] sf::Vector2f upperCenterToUpperLeft(
            const sf::Vector2f& originalPosition) const;

    int mLookDirection;
    float mMaxVelocity;
    EntityType mType;
};

std::vector<std::unique_ptr<Entity>>& getEntities();
void addEntity(std::unique_ptr<Entity> entity);
void addEntityToFront(std::unique_ptr<Entity> entity);

#endif  // SUPERMARIOBROS_ENTITY_H
