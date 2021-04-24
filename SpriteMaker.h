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

    sf::Texture enemyTexture;
    sf::Texture playerTexture;
    sf::Texture inanimateObjectTexture;
};

void initializeSpriteMaker(const std::string& resourceDir);
std::unique_ptr<SpriteMaker>& getSpriteMaker();

#endif  // SUPERMARIOBROS_SPRITEMAKER_H
