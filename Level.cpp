#include "Level.h"

#include <cmath>

Level::Level(std::unique_ptr<Mario> mario,
             std::vector<std::unique_ptr<Entity>>&& entities) :
    mMario(std::move(mario)),
    mEntities(std::move(entities))
{
}

void Level::executeFrame(const KeyboardInput& input)
{
    // Reset mDeltaP
    mMario->mDeltaP.x = 0;
    mMario->mDeltaP.y = 0;

    for (auto& entity : mEntities)
    {
        entity->mDeltaP.x = 0;
        entity->mDeltaP.y = 0;
    }

    setMarioMovementFromController(input);
    mMario->updatePosition();

    for (auto& entity : mEntities)
    {
        entity->updatePosition();
    }

    mMario->collideWithEntity(mEntities);
    for (size_t ii = 0; ii < mEntities.size(); ++ii)
        for (size_t jj = ii + 1; jj < mEntities.size(); ++jj)
            mEntities[ii]->collideWithEntity(mEntities[jj]);

    mMario->updateAnimation();

    for (auto& entity : mEntities)
    {
        entity->updateAnimation();
    }

    mEntities.erase(std::remove_if(mEntities.begin(),
                                   mEntities.end(),
                                   [](std::unique_ptr<Entity>& entity) {
                                       return entity->needsCleanup();
                                   }),
                    mEntities.end());
}

void Level::drawFrame(sf::RenderWindow& window)
{
    window.clear(sf::Color(0, 0, 255, 255));
    mMario->draw(window);
    for (auto& entity : mEntities)
    {
        entity->draw(window);
    }
}

void Level::setMarioMovementFromController(const KeyboardInput& currentInput)
{
    if (mMario->isFalling())
    {
        return;
    }
    if (currentInput.B.pressedThisFrame())
    {
        mMario->setForm(MarioForm::BIG_MARIO);
    }
    else if (currentInput.B.releasedThisFrame())
    {
        mMario->setForm(MarioForm::SMALL_MARIO);
    }

    sf::Vector2f acceleration = mMario->getAcceleration();
    sf::Vector2f velocity = mMario->getVelocity();
    if (currentInput.A.pressedThisFrame() && velocity.y == 0)
    {
        if (std::fabs(velocity.x) < 37.0 / 16.0)
        {
            velocity.y = -4.0;
        }
        else
        {
            velocity.y = -5.0;
        }
    }
    if (currentInput.A.keyIsDown)
    {
        if (std::fabs(velocity.x) < 1.0)
        {
            acceleration.y = 1.0 / 8.0;
        }
        else if (std::fabs(velocity.x) < 37.0 / 16.0)
        {
            acceleration.y = 0.1172;
        }
        else
        {
            acceleration.y = 0.15625;
        }
        mMario->setJumping(true);
    }
    else
    {
        if (std::fabs(velocity.x) < 1.0)
        {
            acceleration.y = 7.0 / 16.0;
        }
        else if (std::fabs(velocity.x) < 37.0 / 16.0)
        {
            acceleration.y = 6.0 / 16.0;
        }
        else
        {
            acceleration.y = 9.0 / 16.0;
        }
    }

    if (currentInput.right.keyIsDown)
    {
        if (!currentInput.left.keyIsDown)
            acceleration.x = 1;
    }
    if (currentInput.left.keyIsDown)
    {
        if (!currentInput.right.keyIsDown)
            acceleration.x = -1;
    }
    if ((currentInput.left.releasedThisFrame() &&
         !currentInput.right.keyIsDown) ||
        (currentInput.right.releasedThisFrame() &&
         !currentInput.left.keyIsDown))
    {
        // TODO: Should we decelerate to 0?
        velocity.x = 0;
        acceleration.x = 0;
    }

    mMario->setAcceleration(acceleration);
    mMario->setVelocity(velocity);
}

const Mario& Level::getMario() const
{
    return *mMario;
}