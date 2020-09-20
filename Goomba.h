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

    void updateAnimation();

private:
    Animation* mActiveAnimation;
    sf::Texture mTexture;
    Animation walkingAnimation;
};

#endif  // SUPERMARIOBROS_GOOMBA_H
