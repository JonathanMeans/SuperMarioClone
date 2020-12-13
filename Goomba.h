#ifndef SUPERMARIOBROS_GOOMBA_H
#define SUPERMARIOBROS_GOOMBA_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System.hpp>
#include "Animation.h"

#include "Entity.h"

class Goomba : public Entity
{
public:
    explicit Goomba(std::shared_ptr<sf::Sprite> sprite);

    void die() override;

private:
    void onCollision(const Collision& collision) override;

    Animation walkingAnimation;
    Animation deathAnimation;
};

#endif  // SUPERMARIOBROS_GOOMBA_H
