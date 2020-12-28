#ifndef SUPERMARIOBROS_UTILS_H
#define SUPERMARIOBROS_UTILS_H

#include <SFML/System.hpp>

class Utils
{
public:
    static bool IsIntersecting(sf::Vector2f a,  sf::Vector2f b, sf::Vector2f c, sf::Vector2f d);
    static bool IsOnLeft(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);
    static bool IsOnRight(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);
    static bool IsCollinear(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);
    static float Area2( sf::Vector2f a,  sf::Vector2f b,  sf::Vector2f c);
};

#endif  // SUPERMARIOBROS_UTILS_H
