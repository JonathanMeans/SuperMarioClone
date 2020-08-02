#ifndef SUPERMARIOBROS_ANIMATION_H
#define SUPERMARIOBROS_ANIMATION_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <cstdlib>
#include <memory>
enum class AnimationType
{
    WALKING,
    JUMPING,
    STANDING
};

class Animation
{
public:
    Animation();
    void load(AnimationType type,
              const std::shared_ptr<sf::Sprite>& activeSprite);
    std::shared_ptr<sf::Sprite> processAction();
    void setPosition(size_t x, size_t y);

private:
    sf::Texture mTexture;
    size_t mRemainingTicsThisFrame{};
    size_t mTicsPerFrame{};
    size_t mSpriteIndex{};
    bool repeat{};

    std::vector<sf::IntRect> mActionRectangles;
    std::shared_ptr<sf::Sprite> mActiveSprite;

    void generateRectangles(size_t numRectangles, size_t initialOffset);
};

#endif  // SUPERMARIOBROS_ANIMATION_H
