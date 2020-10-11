#ifndef SUPERMARIOBROS_SPRITEMAKER_H
#define SUPERMARIOBROS_SPRITEMAKER_H

#include <string>
#include <memory>
#include "SFML/Graphics.hpp"

class SpriteMaker
{
public:
    explicit SpriteMaker(const std::string& resourcesDir);

    sf::Texture goombaTexture;
    std::shared_ptr<sf::Sprite> goombaSprite;

    sf::Texture marioTexture;
    std::shared_ptr<sf::Sprite> marioSprite;

};

#endif  // SUPERMARIOBROS_SPRITEMAKER_H
