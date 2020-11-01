#include <SFML/System.hpp>
#include <Utils.h>

namespace
{
bool lineContainsPoint(sf::Vector2f lineStart, sf::Vector2f lineEnd, sf::Vector2f point)
{
    if (lineStart.y == lineEnd.y && lineStart.y == point.y)
    {
        const auto left = std::min(lineStart.x, lineEnd.x);
        const auto right = std::max(lineStart.x, lineEnd.x);
        return left <= point.x && point.x <= right;
    }
    if (lineStart.x == lineEnd.x && lineStart.x == point.x)
    {
        const auto top = std::min(lineStart.y, lineEnd.y);
        const auto bottom = std::max(lineStart.y, lineEnd.y);
        return top <= point.x && point.x <= bottom;
    }
    return false;

}
}
bool Utils::IsIntersecting(sf::Vector2f a,  sf::Vector2f b, sf::Vector2f c, sf::Vector2f d)
{
    if (lineContainsPoint(c, d, a) || lineContainsPoint(c, d, b))
        return true;
    return !IsCollinear(a, b, c) && !IsCollinear(a, b, d)
            && ((IsOnLeft(a, b, c) && IsOnRight(a, b, d)) || (IsOnLeft(a, b, d) && IsOnRight(a, b, c)));
}

bool Utils::IsOnLeft(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c)
{
    return Area2(a, b, c) > 0;
}

bool Utils::IsOnRight(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c)
{
    return Area2(a, b, c) < 0;
}

bool Utils::IsCollinear(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c)
{
    return Area2(a, b, c) == 0;
}

int Utils::Area2( sf::Vector2f a,  sf::Vector2f b,  sf::Vector2f c)
{
    return (b.x - a.x) * (c.y - a.y) -
           (c.x - a.x) * (b.y - a.y);
}

