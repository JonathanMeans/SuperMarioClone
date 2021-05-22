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
              std::vector<sf::IntRect> actionRectangles,
              bool repeat,
              size_t ticsPerFrame,
              const std::shared_ptr<AnimationBuilder>& animationBuilder);
    void processAction();

    [[nodiscard]] size_t getSpriteIndex() const;

    [[nodiscard]] bool finished() const;

    Animation switchPalette(const sf::Vector2f& offset, const sf::Vector2f& size);

private:
    size_t mRemainingTicsThisFrame{};
    size_t mTicsPerFrame{};
    size_t mSpriteIndex{};
    bool mRepeat{};

    std::vector<sf::IntRect> mActionRectangles;
    sf::Sprite* mActiveSprite = nullptr;
    std::shared_ptr<AnimationBuilder> mAnimationBuilder;
};

#endif  // SUPERMARIOBROS_ANIMATION_H
