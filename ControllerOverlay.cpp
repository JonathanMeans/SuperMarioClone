#include "ControllerOverlay.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

void ControllerOverlay::draw(const KeyboardInput& keyboardInput, sf::RenderWindow& window)
{
    // Keypad
    const auto view = window.getView();
    const auto leftOffset = view.getCenter().x - (view.getSize().x / 2);
    sf::RectangleShape left(sf::Vector2f(10, 5));
    sf::RectangleShape right(sf::Vector2f(10, 5));
    sf::RectangleShape up(sf::Vector2f(5, 10));
    sf::RectangleShape down(sf::Vector2f( 5, 10));

    sf::Color red = sf::Color(150, 0, 0);
    sf::Color green = sf::Color(0, 150, 0);

    left.setFillColor(keyboardInput.left.keyIsDown ? green : red);
    right.setFillColor(keyboardInput.right.keyIsDown ? green : red);
    up.setFillColor(keyboardInput.up.keyIsDown ? green : red);
    down.setFillColor(keyboardInput.down.keyIsDown ? green : red);


    left.setPosition(leftOffset + 120, 180);
    right.setPosition(leftOffset + 135, 180);
    up.setPosition(leftOffset + 130, 170);
    down.setPosition(leftOffset + 130, 185);

    window.draw(left);
    window.draw(right);
    window.draw(up);
    window.draw(down);

    // Buttons
    sf::CircleShape bButton(5);
    sf::CircleShape aButton(5);

    bButton.setFillColor(keyboardInput.B.keyIsDown ? green : red);
    aButton.setFillColor(keyboardInput.A.keyIsDown ? green : red);

    bButton.setPosition(leftOffset + 150, 178);
    aButton.setPosition(leftOffset + 165, 178);

    window.draw(bButton);
    window.draw(aButton);
}