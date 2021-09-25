#ifndef SUPERMARIOBROS_FIREBALL_H
#define SUPERMARIOBROS_FIREBALL_H

#include "Entity.h"

class Fireball : public Entity
        {
        public:
            Fireball(const sf::Texture& texture, const sf::Vector2f& position, int direction);

	    static float width() { return 8; }

        private:
            Animation defaultAnimation;
        };

#endif  // SUPERMARIOBROS_FIREBALL_H
