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
    explicit Mario(const std::string& resourcesDir);
    void draw(sf::RenderWindow& window);

    void walk();

    void setPosition(size_t x, size_t y);
    size_t getX() const;
    size_t getY() const;

    void stopWalking();

    void jump();
    void setForm(MarioForm form);

    // TODO: Make the difference between these more clear
    void setAnimation();
    void updateAnimation();

    void setAcceleration(const sf::Vector2<float>& setVelocity);
    void updatePosition();

    void setVelocity(const sf::Vector2f& newVelocity);
    [[nodiscard]] sf::Vector2f getVelocity() const;
    [[nodiscard]] sf::Vector2f getAcceleration() const;

private:
    const float mMaxVelocity;
    sf::Vector2f mVelocity;
    sf::Vector2f mAcceleration;

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

    bool mChangingDirection;
    int mLookDirection;
};

#endif  // SUPERMARIOBROS_MARIO_H
