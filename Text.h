#ifndef SUPERMARIOBROS_TEXT_H
#define SUPERMARIOBROS_TEXT_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <string>

void initializeHUDOverlay(const std::string& resourceDir);

class Text
{
public:
    Text(const std::string& content, const sf::Vector2f& position);
    virtual ~Text()
    {
    }

    void updateString(const std::string& newString);

    void draw(sf::RenderWindow& window) const;

private:
    sf::Text mSfText;
};

class Points : public Text
{
public:
    Points(size_t numPoints, const sf::Vector2f& position);

    void addPoints(size_t newPoints);

private:
    static std::string formatPoints(size_t numPoints);

    size_t mNumPoints;
};

std::shared_ptr<Points> getPoints();

#endif  // SUPERMARIOBROS_TEXT_H
