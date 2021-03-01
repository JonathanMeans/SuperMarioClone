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
    STANDING,

    BIG_WALKING,
    BIG_JUMPING,
    BIG_STANDING,

    GOOMBA_WALKING,
    GOOMBA_DEATH,

    MARIO_DEATH,
    PIPE,
    BLOCK
};

class Animation
{
public:
    Animation();
    void load(AnimationType type, sf::Sprite& activeSprite);
    void processAction();

    [[nodiscard]] size_t getSpriteIndex() const;

private:
    size_t mRemainingTicsThisFrame{};
    size_t mTicsPerFrame{};
    size_t mSpriteIndex{};
    bool repeat{};

    std::vector<sf::IntRect> mActionRectangles;
    sf::Sprite* mActiveSprite = nullptr;

    void generateRectangles(size_t numRectangles,
                            size_t initialOffset,
                            size_t yOffset,
                            size_t rectHeight,
                            size_t rectXOffset,
                            size_t rectWidth);
    void generateStaticAnimation(size_t xOffset, size_t yOffset, size_t width, size_t height);
};

#endif  // SUPERMARIOBROS_ANIMATION_H
