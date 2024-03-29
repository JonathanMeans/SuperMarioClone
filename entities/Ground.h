#ifndef SUPERMARIOBROS_GROUND_H
#define SUPERMARIOBROS_GROUND_H

#include "Entity.h"

class Ground : public Entity
{
public:
    Ground(const sf::Texture& texture, const sf::Vector2f& position);

private:
    Animation defaultAnimation;
};

#endif  // SUPERMARIOBROS_GROUND_H
