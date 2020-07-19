#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works!");
  window.clear();

  sf::Texture texture;
  if (!texture.loadFromFile("../resources/Mario & Luigi.png", sf::IntRect(34, 80, 16, 16)))
  {
      std::cerr << "Error Loading Texture";
  }
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setPosition(sf::Vector2f(10.f, 50.f);
  window.draw(sprite);



  while (window.isOpen())
  {
    sf::Event event = {};
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    window.display();
  }

  return 0;
}