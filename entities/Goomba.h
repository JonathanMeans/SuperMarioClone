#ifndef SUPERMARIOBROS_GOOMBA_H
#define SUPERMARIOBROS_GOOMBA_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System.hpp>
#include "Animation.h"

#include "Entity.h"

class Goomba : public Entity
{
public:
    Goomba(const sf::Texture& texture, const sf::Vector2f& position);

    void terminate() override;

private:
    void onCollision(const Collision& collision) override;

    Animation walkingAnimation;
    Animation deathAnimation;
};

#endif  // SUPERMARIOBROS_GOOMBA_H
