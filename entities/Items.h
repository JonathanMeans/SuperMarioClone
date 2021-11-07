#ifndef SUPERMARIOBROS_ITEMS_H
#define SUPERMARIOBROS_ITEMS_H

#include <Animation.h>
#include <Entity.h>
#include <Level.h>

class Mushroom : public Entity
{
public:
    // The blockTop arguments gives the position of the top of the block whence
    // the Mushroom emerges. This is needed so we know when to stop
    // "growing" out of the block
    Mushroom(const sf::Texture& texture,
             const sf::Vector2f& position,
             float blockTop);

protected:
    void onCollision(const Collision& collision) override;
    void terminate() override;
    void doInternalCalculations() override;

private:
    const float mBlockTop;
    Animation defaultAnimation;
};

class Fireflower : public Entity
{
public:
    // The blockTop arguments gives the position of the top of the block whence
    // the Mushroom emerges. This is needed so we know when to stop
    // "growing" out of the block
    Fireflower(const sf::Texture& texture,
               const sf::Vector2f& position,
               float blockTop);

protected:
    void onCollision(const Collision& collision) override;
    void terminate() override;
    void doInternalCalculations() override;

private:
    const float mBlockTop;
    Animation defaultAnimation;
};

#endif  // SUPERMARIOBROS_ITEMS_H
