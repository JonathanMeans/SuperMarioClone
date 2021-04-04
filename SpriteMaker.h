#ifndef SUPERMARIOBROS_SPRITEMAKER_H
#define SUPERMARIOBROS_SPRITEMAKER_H

#include <memory>
#include <string>
#include "Entity.h"
#include "SFML/Graphics.hpp"

class SpriteMaker
{
public:
    explicit SpriteMaker(const std::string& resourcesDir);

    sf::Sprite goombaSprite;
    sf::Sprite marioSprite;
    sf::Sprite pipeSprite;
    sf::Sprite groundSprite;
    sf::Sprite blockSprite;

private:
    sf::Texture enemiesTexture;
    sf::Texture playerTexture;
    sf::Texture inanimateObjectTexture;
};

#endif  // SUPERMARIOBROS_SPRITEMAKER_H
