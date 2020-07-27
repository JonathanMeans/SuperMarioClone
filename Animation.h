#ifndef SUPERMARIOBROS_ANIMATION_H
#define SUPERMARIOBROS_ANIMATION_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <cstdlib>
enum class AnimationType { WALKING, JUMPING, STANDING };

class Animation
{
public:
    Animation();
    void load(AnimationType type, size_t initialX, size_t initialY, const sf::Texture& texture);
    sf::Sprite* getActiveSprite();
    sf::Sprite* processAction();
    void setPosition(size_t x, size_t y);

private:
    size_t mX;
    size_t mY;
    size_t mRemainingTicsThisFrame;
    size_t mTicsPerFrame;
    size_t mSpriteIndex;
    bool repeat;

    std::vector<sf::Sprite> mActionSprites;
    sf::Sprite* mActiveSprite{};

    void generateSprites(const size_t numSprites, size_t initialOffset, const sf::Texture& texture);

};




#endif  // SUPERMARIOBROS_ANIMATION_H
