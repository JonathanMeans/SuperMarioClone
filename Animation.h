#ifndef SUPERMARIOBROS_ANIMATION_H
#define SUPERMARIOBROS_ANIMATION_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cstdlib>
#include <memory>

class AnimationBuilder;

class Animation
{
public:
    Animation();
    Animation(sf::Sprite& activeSprite,
              size_t numRect,
              size_t xOffset,
              size_t yOffset,
              size_t width,
              size_t height,
              size_t borderSize,
              bool repeat,
              std::vector<sf::IntRect> actionRectangles,
              size_t ticsPerFrame);
    void processAction();

    [[nodiscard]] size_t getSpriteIndex() const;

    [[nodiscard]] bool finished() const;

    [[nodiscard]] std::vector<sf::IntRect> generateActionRectangles() const;

    void switchPalette(const sf::Vector2f& offset, const sf::Vector2f& size);

private:
    size_t mRemainingTicsThisFrame;
    size_t mTicsPerFrame;
    size_t mSpriteIndex;
    size_t mNumRect;
    size_t mXOffset;
    size_t mYOffset;
    size_t mWidth;
    size_t mHeight;
    size_t mBorderSize;
    bool mRepeat;

    std::vector<sf::IntRect> mActionRectangles;
    sf::Sprite* mActiveSprite = nullptr;
};

#endif  // SUPERMARIOBROS_ANIMATION_H
