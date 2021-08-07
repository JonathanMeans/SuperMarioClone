#ifndef SUPERMARIOBROS_INVISIBLEWALL_H
#define SUPERMARIOBROS_INVISIBLEWALL_H

#include "Entity.h"

class InvisibleWall : public Entity
{
public:
    InvisibleWall(const sf::Texture& texture, const sf::Vector2f& position);

    void draw(sf::RenderWindow& window) override;

private:
    // Needed to make parent ctor happy
    sf::Texture mTexture;
};

#endif  // SUPERMARIOBROS_INVISIBLEWALL_H
