#ifndef SUPERMARIOBROS_MARIO_H
#define SUPERMARIOBROS_MARIO_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Animation.h"
#include "Entity.h"

enum class MarioForm
{
    BIG_MARIO,
    SMALL_MARIO,
    FIRE_MARIO,
};

std::string formToString(MarioForm form);

class Mario : public Entity
{
public:
    static const float MAX_RUNNING_VELOCITY;
    static const float MAX_WALKING_VELOCITY;

    Mario(const sf::Texture& texture, const sf::Vector2f& initialPosition);

    void walk();

    void stopWalking();

    void jump();
    void setForm(MarioForm form);
    MarioForm getForm() const;

    [[nodiscard]] EntityType getType() const override;

    void setAnimationFromState() override;

    inline void setJumping(bool isJumping)
    {
        mJumping = isJumping;
    }

    void terminate() override;

    bool isTransitioning() const;

    bool isJumping() const;

    bool isGrowing() const;

    bool isShrinking() const;

    bool isTransitioningToFire() const;

    const Hitbox& getHitbox(EntityType type) const override;

    void changeToSmallDimensions();

private:
    void onCollision(const Collision& collision) override;

    Hitbox smallHitbox;
    Hitbox largeHitbox;

    MarioForm mForm;

    Animation walkingAnimation;
    Animation jumpingAnimation;
    Animation standingAnimation;
    Animation deathAnimation;

    Animation growingAnimation;
    Animation shrinkingAnimation;
    Animation changeToFireMarioAnimation;

    bool mJumping;
    bool mIsDead;
};

#endif  // SUPERMARIOBROS_MARIO_H
