#include "Mario.h"
#include "Animation.h"

#include <iostream>
#include <memory>
#include "SFML/Graphics.hpp"

namespace
{
const auto MARIO_HEIGHT = 16;
}

void Mario::updatePosition()
{
    mVelocity.x += mAcceleration.x;
    mVelocity.y += mAcceleration.y;
    if (mVelocity.x > 0 && mVelocity.x > mMaxVelocity)
        mVelocity.x = mMaxVelocity;
    if (mVelocity.x < 0 && mVelocity.x < -mMaxVelocity)
        mVelocity.x = -mMaxVelocity;

    // TODO: What to do about y?

    setPosition(getX() + mVelocity.x, getY() + mVelocity.y);
}

Mario::Mario(const std::string& resourcesDir) :
    mMaxVelocity(2.f),
    mAcceleration(0, 1),
    mForm(MarioForm::SMALL_MARIO),
    mVelocity(0, 0),
    mChangingDirection(false),
    mLookDirection(1),
    mJumping(false)
{
    if (!mTexture.loadFromFile(resourcesDir + "Mario & Luigi.png"))
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

    mActiveAnimation = &standingAnimation;
    mActiveAnimation->processAction();

    const auto spriteOrigin = MARIO_HEIGHT / 2;
    mActiveSprite->setOrigin(spriteOrigin, 0);
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

size_t Mario::getHeight() const
{
    if (mForm == MarioForm::SMALL_MARIO)
        return MARIO_HEIGHT;
    else
        return 2 * MARIO_HEIGHT;
}

void Mario::setAnimation()
{
    if (mJumping)
    {
        jump();
    }
    else if (mAcceleration.x != 0)
    {
        walk();
    }
    else
    {
        stopWalking();
    }

    if (mChangingDirection)
    {
        mActiveSprite->scale(-1.f, 1.f);
        mChangingDirection = false;
    }
}

void Mario::updateAnimation()
{
    mActiveAnimation->processAction();
}

void Mario::walk()
{
    switch (mForm)
    {
    case MarioForm::BIG_MARIO:
        mActiveAnimation = &bigWalkingAnimation;
        break;
    case MarioForm::SMALL_MARIO:
        mActiveAnimation = &walkingAnimation;
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
            mActiveAnimation = &bigStandingAnimation;
        }
        else if (form == MarioForm::SMALL_MARIO)
        {
            const auto currentY = mActiveSprite->getPosition().y;
            const auto newY = currentY + MARIO_HEIGHT;
            mActiveSprite->setPosition(mActiveSprite->getPosition().x, newY);
            mActiveAnimation = &standingAnimation;
        }
    }

    mForm = form;
}

void Mario::stopWalking()
{
    switch (mForm)
    {
    case MarioForm::BIG_MARIO:
        mActiveAnimation = &bigStandingAnimation;
        break;
    case MarioForm::SMALL_MARIO:
        mActiveAnimation = &standingAnimation;
        break;
    }
}

void Mario::jump()
{
    switch (mForm)
    {
    case MarioForm::BIG_MARIO:
        mActiveAnimation = &bigJumpingAnimation;
        break;
    case MarioForm::SMALL_MARIO:
        mActiveAnimation = &jumpingAnimation;
        break;
    }
}

int sign(float val)
{
    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

void Mario::setAcceleration(const sf::Vector2<float>& acceleration)
{
    if (acceleration == this->mAcceleration)
        return;

    if (acceleration.x != 0 &&
        (sign(acceleration.x) != sign(static_cast<float>(mLookDirection))))
    {
        mChangingDirection = true;
        mLookDirection *= -1;
    }

    mAcceleration = acceleration;
}

bool Mario::collideWithGround(const size_t groundY)
{
    bool atGround = Fallable::collideWithGround(groundY);
    if (atGround)
    {
        setJumping(false);
    }
    return atGround;
}

sf::Vector2f Mario::getVelocity() const
{
    return mVelocity;
}

void Mario::setVelocity(const sf::Vector2f& newVelocity)
{
    mVelocity = newVelocity;
}

sf::Vector2f Mario::getAcceleration() const
{
    return mAcceleration;
}
