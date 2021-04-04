#ifndef SUPERMARIOBROS_PIPE_H
#define SUPERMARIOBROS_PIPE_H

#include "Entity.h"

class Pipe : public Entity
{
public:
    Pipe(const sf::Texture& texture, const sf::Vector2f& position);

private:
    Animation defaultAnimation;
};

#endif  // SUPERMARIOBROS_PIPE_H
