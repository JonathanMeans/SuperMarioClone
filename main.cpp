#include <iostream>
#include "mario.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(200, 200), "Super Mario Bros");
  window.clear();
  mario sprite;
  sprite.draw(window);
  window.display();

  while (window.isOpen())
  {
    sf::Event event = {};
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
  }

  return 0;
}