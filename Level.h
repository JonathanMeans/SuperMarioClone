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
     * Current, the Level has ownership of Mario, but NOT the entities
     * (because I don't know if a vector of smart pointers is a good idea)
     * TODO: This needs to be consistent
     */
    Level(std::unique_ptr<Mario> mario, std::vector<Entity*> entities);

    void setMarioMovementFromController(const KeyboardInput& currentInput);

    void executeFrame(const KeyboardInput& input);

    [[nodiscard]] const Mario& getMario() const;

private:
    std::unique_ptr<Mario> mMario;
    // TODO: How can we own a vector of entities?
    std::vector<Entity*> mEntities;

    /*
     * Ground height is a large arbitrary number so that Mario and all other
     * entities on the screen are considered above the ground
     * */
    float groundHeight = 500.f;
};

#endif  // SUPERMARIOBROS_LEVEL_H
