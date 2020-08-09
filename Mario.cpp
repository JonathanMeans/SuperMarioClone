#include "Mario.h"
#include "Animation.h"

#include <iostream>
#include <memory>
#include "SFML/Graphics.hpp"

namespace
{
const auto MARIO_HEIGHT = 16;
}

Mario::Mario()
{
    if (!mTexture.loadFromFile("../resources/Mario & Luigi.png"))
    {
        std::cerr << "Error Loading Texture";
        throw std::runtime_error("Unable to load Mario texture");
    }
    mTexture.setSmooth(false);

    mActiveSprite = std::make_shared<sf::Sprite>();
    mActiveSprite->setPosition(100, 100);
    mActiveSprite->setTexture(mTexture);

    walkingAnimation.load(AnimationType::WALKING, mActiveSprite);
    jumpingAnimation.load(AnimationType::JUMPING, mActiveSprite);
    standingAnimation.load(AnimationType::STANDING, mActiveSprite);

    bigWalkingAnimation.load(AnimationType::BIG_WALKING, mActiveSprite);
    bigStandingAnimation.load(AnimationType::BIG_STANDING, mActiveSprite);
    bigJumpingAnimation.load(AnimationType::BIG_JUMPING, mActiveSprite);
}

void Mario::draw(sf::RenderWindow& window)
{
    window.draw(*mActiveSprite);
}

void Mario::setPosition(size_t x, size_t y)
{
    mActiveSprite->setPosition(x, y);
}

size_t Mario::getX() const
{
    return mActiveSprite->getPosition().x;
}

size_t Mario::getY() const
{
    return mActiveSprite->getPosition().y;
}

void Mario::walk()
{
    switch (mForm)
    {
    case MarioForm::BIG_MARIO:
        mActiveSprite = bigWalkingAnimation.processAction();
        break;
    case MarioForm::SMALL_MARIO:
        mActiveSprite = walkingAnimation.processAction();
        break;
    }
}

void Mario::setForm(MarioForm form)
{
    const bool formIsChanging = form != mForm;
    if (formIsChanging)
    {
        if (form == MarioForm::BIG_MARIO)
        {
            const auto currentY = mActiveSprite->getPosition().y;
            const auto newY = currentY - MARIO_HEIGHT;
            mActiveSprite->setPosition(mActiveSprite->getPosition().x, newY);
        }
        else if (form == MarioForm::SMALL_MARIO)
        {
            const auto currentY = mActiveSprite->getPosition().y;
            const auto newY = currentY + MARIO_HEIGHT;
            mActiveSprite->setPosition(mActiveSprite->getPosition().x, newY);
        }
    }

    mForm = form;
}

void Mario::stopWalking()
{
    switch (mForm)
    {
    case MarioForm::BIG_MARIO:
        mActiveSprite = bigStandingAnimation.processAction();
        break;
    case MarioForm::SMALL_MARIO:
        mActiveSprite = standingAnimation.processAction();
        break;
    }
}

void Mario::jump()
{
    switch (mForm)
    {
    case MarioForm::BIG_MARIO:
        mActiveSprite = bigJumpingAnimation.processAction();
        break;
    case MarioForm::SMALL_MARIO:
        mActiveSprite = jumpingAnimation.processAction();
        break;
    }
}
