
#include "Text.h"
#include <cassert>
#include <cassert>
#include <iomanip>

namespace
{
sf::Font font;
bool fontIsInitialized = false;
}

void initializeFonts(const std::string& resourceDir)
{
    const auto fontFile = resourceDir + "/fonts/emulogic.ttf";
    if (!font.loadFromFile(fontFile))
    {
        throw std::runtime_error("Unable to load font from " + fontFile);
    }
    fontIsInitialized = true;
}

Text::Text(const std::string& content, const sf::Vector2f& position)
{
    assert(fontIsInitialized);
    mSfText.setFont(font);
    mSfText.setString(content);
    mSfText.setPosition(position);
    mSfText.setFillColor(sf::Color::White);
    mSfText.setCharacterSize(8);
}

void Text::draw(sf::RenderWindow& window) const
{
    window.draw(mSfText);
}

Points::Points(size_t numPoints, const sf::Vector2f& position) :
    Text(formatPoints(numPoints), position),
    mNumPoints(numPoints)
{
}

std::string Points::formatPoints(size_t numPoints)
{
    auto stringValue = std::to_string(numPoints);
    assert(stringValue.size() <= 6 && "Too many points to handle");
    std::ostringstream str;
    str << std::left << std::setw(6) << std::setfill('0') << stringValue;
    return str.str();
}
