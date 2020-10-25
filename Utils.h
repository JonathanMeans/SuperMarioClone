#ifndef SUPERMARIOBROS_UTILS_H
#define SUPERMARIOBROS_UTILS_H

#include <SFML/System.hpp>

class Utils
{
public:
    bool IsIntersecting(sf::Vector2f a,  sf::Vector2f b, sf::Vector2f c, sf::Vector2f d);
    bool IsOnLeft(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);
    bool IsOnRight(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);
    int Area2( sf::Vector2f a,  sf::Vector2f b,  sf::Vector2f c);
};

#endif  // SUPERMARIOBROS_UTILS_H
