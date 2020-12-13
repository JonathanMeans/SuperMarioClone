#ifndef SUPERMARIOBROS_PIPE_H
#define SUPERMARIOBROS_PIPE_H

#include "Entity.h"

class Pipe : public Entity
{
public:
    explicit Pipe(std::shared_ptr<sf::Sprite> sprite);

private:
    Animation defaultAnimation;
};

#endif  // SUPERMARIOBROS_PIPE_H
