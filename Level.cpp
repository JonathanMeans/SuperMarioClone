#include "Level.h"

#include <utility>

Level::Level(std::unique_ptr<Mario> mario, std::vector<Entity*> entities) :
    mMario(std::move(mario)),
    mEntities(std::move(entities))
{
}


void Level::executeFrame(const KeyboardInput& input)
{
    (void) input;
    mMario->updatePosition();
    mMario->collideWithEnemy(mEntities);

    // Reset mDeltaP
    mMario->mDeltaP.x = 0;
    mMario->mDeltaP.y = 0;
}

const Mario& Level::getMario() const
{
    return *mMario;
}