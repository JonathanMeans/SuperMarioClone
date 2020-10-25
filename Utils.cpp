#include <SFML/System.hpp>
#include <Utils.h>

bool Utils::IsIntersecting(sf::Vector2f a,  sf::Vector2f b, sf::Vector2f c, sf::Vector2f d)
{
    return (IsOnLeft(a, b, c) && IsOnRight(a, b, d)) || (IsOnLeft(a, b, d) && IsOnRight(a, b, c));
}

bool Utils::IsOnLeft(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c)
{
    return Area2(a, b, c) > 0;
}

bool Utils::IsOnRight(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c)
{
    return Area2(a, b, c) < 0;
}

int Utils::Area2( sf::Vector2f a,  sf::Vector2f b,  sf::Vector2f c)
{
    return (b.x - a.x) * (c.y - a.y) -
           (c.x - a.x) * (b.y - a.y);
}

