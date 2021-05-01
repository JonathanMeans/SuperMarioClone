#ifndef SUPERMARIOBROS_ITEMS_H
#define SUPERMARIOBROS_ITEMS_H

#include <Animation.h>
#include <Entity.h>

class Mushroom : public Entity
{
public:
    Mushroom(const sf::Texture& texture, const sf::Vector2f& position);

protected:
    void onCollision(const Collision& collision) override;

private:
    Animation defaultAnimation;
};

#endif  // SUPERMARIOBROS_ITEMS_H
