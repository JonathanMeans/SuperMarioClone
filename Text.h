#ifndef SUPERMARIOBROS_TEXT_H
#define SUPERMARIOBROS_TEXT_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>

void initializeFonts(const std::string& resourceDir);

class Text
{
public:
    Text(const std::string& content, const sf::Vector2f& position);
    virtual ~Text()
    {
    }

    void draw(sf::RenderWindow& window) const;

private:
    sf::Text mSfText;
};

class Points : public Text
{
public:
    Points(size_t numPoints, const sf::Vector2f& position);

private:
    static std::string formatPoints(size_t numPoints);

    size_t mNumPoints;
};

#endif  // SUPERMARIOBROS_TEXT_H
