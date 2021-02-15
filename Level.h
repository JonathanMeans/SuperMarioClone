#ifndef SUPERMARIOBROS_LEVEL_H
#define SUPERMARIOBROS_LEVEL_H

#include "Mario.h"
#include "Input.h"

/*
 * Encapsulates the game logic and entities for a single level.
 */
class Level
{
public:
    /*
     * Construct a new level from Mario and the entities in the level.
     * Current, the Level has ownership of Mario and the entities
     */
    Level(std::unique_ptr<Mario> mario, std::vector<std::unique_ptr<Entity>> entities, float groundHeight);

    void setMarioMovementFromController(const KeyboardInput& currentInput);

    void executeFrame(const KeyboardInput& input);

    void drawFrame(sf::RenderWindow& window);

    [[nodiscard]] const Mario& getMario() const;

private:
    std::unique_ptr<Mario> mMario;
    std::vector<std::unique_ptr<Entity>> mEntities;

    /*
     * Ground height is a large arbitrary number so that Mario and all other
     * entities on the screen are considered above the ground
     * */
    float mGroundHeight;
};

#endif  // SUPERMARIOBROS_LEVEL_H
