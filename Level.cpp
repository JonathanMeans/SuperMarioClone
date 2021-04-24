#include "Level.h"

#include <cmath>

Level::Level(std::unique_ptr<Mario> mario,
             std::vector<std::unique_ptr<Entity>>&& entities) :
    mMario(std::move(mario))
{
    for (auto& entity : entities)
        addEntity(std::move(entity));
}

void Level::executeFrame(const KeyboardInput& input)
{
    // Reset mDeltaP
    mMario->mDeltaP.x = 0;
    mMario->mDeltaP.y = 0;

    for (auto& entity : getEntities())
    {
        entity->mDeltaP.x = 0;
        entity->mDeltaP.y = 0;
    }

    setMarioMovementFromController(input);
    mMario->updatePosition();

    for (auto& entity : getEntities())
    {
        entity->updatePosition();
        entity->doInternalCalculations();
    }

    mMario->collideWithEntity(getEntities());
    for (size_t ii = 0; ii < getEntities().size(); ++ii)
        for (size_t jj = ii + 1; jj < getEntities().size(); ++jj)
            getEntities()[ii]->collideWithEntity(getEntities()[jj]);

    mMario->updateAnimation();

    for (auto& entity : getEntities())
    {
        entity->updateAnimation();
    }

    getEntities().erase(std::remove_if(getEntities().begin(),
                                       getEntities().end(),
                                       [](std::unique_ptr<Entity>& entity) {
                                           return entity->needsCleanup();
                                       }),
                        getEntities().end());
}

void Level::drawFrame(sf::RenderWindow& window)
{
    window.clear(sf::Color(0, 0, 255, 255));
    mMario->draw(window);
    for (auto& entity : getEntities())
    {
        entity->draw(window);
    }
}

void Level::setMarioMovementFromController(const KeyboardInput& currentInput)
{
    setMarioFormFromController(currentInput);

    sf::Vector2f acceleration = mMario->getAcceleration();
    sf::Vector2f velocity = mMario->getVelocity();

    velocity.y = setVerticalVelocityDueToJumpStart(currentInput, velocity);
    if (currentInput.A.pressedThisFrame())
    {
        mMario->setJumping(true);
    }

    acceleration.y = calculateVerticalAcceleration(currentInput, velocity.x);

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

float Level::calculateVerticalAcceleration(const KeyboardInput& currentInput,
                                           float xVelocity) const
{
    float result = 0;
    const auto xSpeed = std::fabs(xVelocity);
    if (currentInput.A.keyIsDown)
    {
        if (xSpeed < 1.0)
        {
            result = 1.0 / 8.0;
        }
        else if (xSpeed < 37.0 / 16.0)
        {
            result = 0.1172;
        }
        else
        {
            result = 0.15625;
        }
    }
    else
    {
        if (xSpeed < 1.0)
        {
            result = 7.0 / 16.0;
        }
        else if (xSpeed < 37.0 / 16.0)
        {
            result = 6.0 / 16.0;
        }
        else
        {
            result = 9.0 / 16.0;
        }
    }
    return result;
}

float Level::setVerticalVelocityDueToJumpStart(
        const KeyboardInput& currentInput, const sf::Vector2f& velocity) const
{
    float result = velocity.y;
    if (!mMario->isJumping() && currentInput.A.pressedThisFrame())
    {
        if (std::fabs(velocity.x) < 37.0 / 16.0)
        {
            result = -4.0;
        }
        else
        {
            result = -5.0;
        }
    }
    return result;
}

void Level::setMarioFormFromController(const KeyboardInput& currentInput) const
{
    if (currentInput.B.pressedThisFrame())
    {
        mMario->setForm(MarioForm::BIG_MARIO);
    }
    else if (currentInput.B.releasedThisFrame())
    {
        mMario->setForm(MarioForm::SMALL_MARIO);
    }
}

const Mario& Level::getMario() const
{
    return *mMario;
}