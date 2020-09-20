#ifndef SUPERMARIOBROS_GOOMBA_H
#define SUPERMARIOBROS_GOOMBA_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System.hpp>
#include "Animation.h"

#include "Fallable.h"

class Goomba : public Fallable
{
public:
    explicit Goomba(const std::string& resourcesDir);
    void draw(sf::RenderWindow& window);

    void setPosition(size_t x, size_t y) override;
    size_t getX() const override;
    size_t getY() const override;
    size_t getHeight() const override;
    void updateAnimation();

    void setAcceleration(const sf::Vector2<float>& setVelocity);

    void setVelocity(const sf::Vector2f& newVelocity) override;
    [[nodiscard]] sf::Vector2f getVelocity() const override;
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
