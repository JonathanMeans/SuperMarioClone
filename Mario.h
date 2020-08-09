#ifndef SUPERMARIOBROS_MARIO_H
#define SUPERMARIOBROS_MARIO_H

#include "Animation.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

enum class MarioForm
{
    BIG_MARIO,
    SMALL_MARIO
};

class Mario
{
public:
    Mario();
    void draw(sf::RenderWindow& window);

    void walk();

    void setPosition(size_t x, size_t y);
    size_t getX() const;
    size_t getY() const;

    void stopWalking();

    void jump();
    void setForm(MarioForm form);
    void updateAnimation();

private:
    std::shared_ptr<sf::Sprite> mActiveSprite;
    sf::Texture mTexture;

    MarioForm mForm;

    Animation walkingAnimation;
    Animation jumpingAnimation;
    Animation standingAnimation;

    Animation bigWalkingAnimation;
    Animation bigJumpingAnimation;
    Animation bigStandingAnimation;

    Animation* mActiveAnimation;
};

#endif  // SUPERMARIOBROS_MARIO_H
