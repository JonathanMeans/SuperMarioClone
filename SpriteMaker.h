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
    std::shared_ptr<sf::Sprite> goombaSprite;

    sf::Texture marioTexture;
    std::shared_ptr<sf::Sprite> marioSprite;

    sf::Texture pipeTexture;
    std::shared_ptr<sf::Sprite> pipeSprite;
};

#endif  // SUPERMARIOBROS_SPRITEMAKER_H
