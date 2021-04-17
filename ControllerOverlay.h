#ifndef SUPERMARIOBROS_CONTROLLEROVERLAY_H
#define SUPERMARIOBROS_CONTROLLEROVERLAY_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "Input.h"
class ControllerOverlay
{
public:
    static void draw(const KeyboardInput& keyboardInput, sf::RenderWindow& window);
};

#endif  // SUPERMARIOBROS_CONTROLLEROVERLAY_H
