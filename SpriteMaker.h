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

    sf::Texture goombaTexture;
    sf::Sprite goombaSprite;

    sf::Texture marioTexture;
    sf::Sprite marioSprite;

    sf::Texture pipeTexture;
    sf::Sprite pipeSprite;
};

#endif  // SUPERMARIOBROS_SPRITEMAKER_H
