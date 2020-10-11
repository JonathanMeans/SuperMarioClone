#ifndef SUPERMARIOBROS_MARIO_H
#define SUPERMARIOBROS_MARIO_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Animation.h"
#include "Entity.h"
#include "Goomba.h"

enum class MarioForm
{
    BIG_MARIO,
    SMALL_MARIO
};

class Mario : public Entity
{
public:
    explicit Mario(const std::shared_ptr<sf::Sprite> sprite);
    void draw(sf::RenderWindow& window);

    void walk();

    size_t getHeight() const override;

    void stopWalking();

    void jump();
    void setForm(MarioForm form);

    // TODO: Make the difference between these more clear
    void setAnimation();

    bool collideWithGround(size_t groundY) override;
    bool collideWithEnemy(std::vector<Goomba> &enemies);

    inline void setJumping(bool isJumping)
    {
        mJumping = isJumping;
    }

private:
    MarioForm mForm;

    Animation walkingAnimation;
    Animation jumpingAnimation;
    Animation standingAnimation;

    Animation bigWalkingAnimation;
    Animation bigJumpingAnimation;
    Animation bigStandingAnimation;

    bool mJumping;
};

#endif  // SUPERMARIOBROS_MARIO_H
