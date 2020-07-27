#ifndef SUPERMARIOBROS_MARIO_H
#define SUPERMARIOBROS_MARIO_H

#include "Animation.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
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

private:
    sf::Texture mTexture;

    sf::Sprite* mActiveSprite{};

    Animation walkingAnimation;
    Animation jumpingAnimation;
    Animation standingAnimation;

    // Walking animation
//    std::vector<sf::Sprite> mWalkingSprites;
//    size_t mSpriteIndex;
//    size_t mTicksPerFrame;
//    size_t mRemainingTicsThisFrame;

    // Jumping animation
//    std::vector<sf::Sprite> mJumpingSprites;
//    size_t mJumpingIndex;
//    size_t mJumpingTicksPerFrame;
//    size_t mJumpingRemainingTicsThisFrame;
};

#endif  // SUPERMARIOBROS_MARIO_H
