#ifndef SUPERMARIOBROS_ANIMATION_H
#define SUPERMARIOBROS_ANIMATION_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <cstdlib>
#include <memory>

class Animation
{
public:
    Animation();
    Animation(sf::Sprite& activeSprite,
              std::vector<sf::IntRect> actionRectangles,
              bool repeat,
              size_t ticsPerFrame);
    void processAction();

    [[nodiscard]] size_t getSpriteIndex() const;

private:
    size_t mRemainingTicsThisFrame{};
    size_t mTicsPerFrame{};
    size_t mSpriteIndex{};
    bool mRepeat{};

    std::vector<sf::IntRect> mActionRectangles;
    sf::Sprite* mActiveSprite = nullptr;
};

#endif  // SUPERMARIOBROS_ANIMATION_H
