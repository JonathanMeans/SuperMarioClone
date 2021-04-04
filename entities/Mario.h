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
    SMALL_MARIO
};

class Mario : public Entity
{
public:
    Mario(const sf::Texture& texture, const sf::Vector2f& initialPosition);

    void walk();

    void stopWalking();

    void jump();
    void setForm(MarioForm form);

    void setAnimationFromState() override;

    inline void setJumping(bool isJumping)
    {
        mJumping = isJumping;
    }

    void die() override;

    const Hitbox& getHitbox(EntityType type) const override;

private:
    void onCollision(const Collision& collision) override;

    Hitbox smallHitbox;
    Hitbox largeHitbox;

    MarioForm mForm;

    Animation walkingAnimation;
    Animation jumpingAnimation;
    Animation standingAnimation;
    Animation deathAnimation;

    Animation bigWalkingAnimation;
    Animation bigJumpingAnimation;
    Animation bigStandingAnimation;

    bool mJumping;
    bool mIsDead;
};

#endif  // SUPERMARIOBROS_MARIO_H
