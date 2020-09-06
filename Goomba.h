#ifndef SUPERMARIOBROS_GOOMBA_H
#define SUPERMARIOBROS_GOOMBA_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System.hpp>
#include "Animation.h"

class Goomba
{
public:
    explicit Goomba(const std::string& resourcesDir);
    void draw(sf::RenderWindow& window);

    void setPosition(size_t x, size_t y);
    size_t getX() const;
    size_t getY() const;
    void updateAnimation();

    size_t getBottomPosition() const;
    void setBottomPosition(size_t newBottomY);

    void setAcceleration(const sf::Vector2<float>& setVelocity);
    void updatePosition();

    void setVelocity(const sf::Vector2f& newVelocity);
    [[nodiscard]] sf::Vector2f getVelocity() const;
    [[nodiscard]] sf::Vector2f getAcceleration() const;

private:
    std::shared_ptr<sf::Sprite> mActiveSprite;
    Animation* mActiveAnimation;
    sf::Texture mTexture;
    Animation walkingAnimation;

    sf::Vector2f mVelocity;
    sf::Vector2f mAcceleration;
};

#endif  // SUPERMARIOBROS_GOOMBA_H
