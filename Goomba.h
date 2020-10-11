#ifndef SUPERMARIOBROS_GOOMBA_H
#define SUPERMARIOBROS_GOOMBA_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System.hpp>
#include "Animation.h"

#include "Entity.h"

class Goomba : public Entity
{
public:
    explicit Goomba(const std::shared_ptr<sf::Sprite> sprite);

private:
    Animation walkingAnimation;
};

#endif  // SUPERMARIOBROS_GOOMBA_H
