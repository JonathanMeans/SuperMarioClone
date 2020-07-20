#ifndef SUPERMARIOBROS_MARIO_H
#define SUPERMARIOBROS_MARIO_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
class mario
{
    public:
        mario();
        void draw(sf::RenderWindow& window);

    private:
        sf::Texture mTexture;
        sf::Sprite sprite;

};

#endif  // SUPERMARIOBROS_MARIO_H
