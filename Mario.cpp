#include "Mario.h"
#include "Animation.h"
#include "Hitbox.h"
#include "Timer.h"
#include "Utils.h"

#include <iostream>
#include <memory>

Mario::Mario(const sf::Sprite& sprite, const sf::Vector2f& position) :
    Entity(sprite,
           16,
           16,
           Hitbox(*this, {8, 11}, {4, 5}),
           EntityType::MARIO,
           position,
           2.f),
    smallHitbox(this->mHitbox),
    largeHitbox(*this, {12, 23}, {2, 8}),
    mForm(MarioForm::SMALL_MARIO),
    mJumping(false),
    mIsDead(false)
{
    walkingAnimation.load(AnimationType::WALKING, mActiveSprite);
    jumpingAnimation.load(AnimationType::JUMPING, mActiveSprite);
    standingAnimation.load(AnimationType::STANDING, mActiveSprite);
    deathAnimation.load(AnimationType::MARIO_DEATH, mActiveSprite);

    bigWalkingAnimation.load(AnimationType::BIG_WALKING, mActiveSprite);
    bigStandingAnimation.load(AnimationType::BIG_STANDING, mActiveSprite);
    bigJumpingAnimation.load(AnimationType::BIG_JUMPING, mActiveSprite);

    mActiveAnimation = &standingAnimation;
    mActiveAnimation->processAction();
}

void Mario::setAnimationFromState()
{
    if (mIsDead)
    {
        mActiveAnimation = &deathAnimation;
    }
    else if (mJumping)
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
        mActiveSprite.scale(-1.f, 1.f);
        mChangingDirection = false;
    }
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
            const auto currentY = mActiveSprite.getPosition().y;
            const auto newY = currentY - GRIDBOX_SIZE;
            mActiveSprite.setPosition(mActiveSprite.getPosition().x, newY);
            mActiveAnimation = &bigStandingAnimation;
            mSpriteHeight *= 2;
            mHitbox = largeHitbox;
        }
        else if (form == MarioForm::SMALL_MARIO)
        {
            const auto currentY = mActiveSprite.getPosition().y;
            const auto newY = currentY + GRIDBOX_SIZE;
            mActiveSprite.setPosition(mActiveSprite.getPosition().x, newY);
            mActiveAnimation = &standingAnimation;
            mSpriteHeight /= 2;
            mHitbox = smallHitbox;
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

bool Mario::collideWithGround(float groundY)
{
    if (!mIsDead)
    {
        bool atGround = Entity::collideWithGround(groundY);
        if (atGround)
        {
            setJumping(false);
        }
        return atGround;
    }
    return false;
}

void Mario::onCollision(const Collision& collision)
{
    // collision's side is referring to the side of Mario that collided
    if (isEnemy(collision.entityType))
    {
        if (collision.side != EntitySide::BOTTOM)
        {
            die();
        }
        else
        {
            addPositionDelta(0, -5);
        }
    }
    else
    {
        if (collision.side == EntitySide::BOTTOM)
        {
            auto spriteBottom = getBottom();
            auto newSpriteBottom = collision.yIntersection;
            const auto delta = newSpriteBottom - spriteBottom;
            addPositionDelta(0, delta);

            const auto currentVelocity = getVelocity();
            setVelocity(sf::Vector2f(currentVelocity.x, 0));
            setJumping(false);
        }
        else if (collision.side == EntitySide::TOP)
        {
            setVelocity(sf::Vector2f(getVelocity().x, 0));
            // TODO: Bug: We want to clip to the bottom of the object
            mDeltaP.y = 0;
        }
        else if (collision.side == EntitySide::RIGHT)
        {
            auto spriteRight = getRight();
            auto newSpriteRight = collision.xIntersection;
            const auto delta = newSpriteRight - spriteRight;
            addPositionDelta(0, delta);
            setVelocity(sf::Vector2f(0, getVelocity().y));
        }
        else if (collision.side == EntitySide::LEFT)
        {
            auto spriteLeft= getLeft();
            auto newSpriteLeft= collision.xIntersection;
            const auto delta = newSpriteLeft - spriteLeft;
            addPositionDelta(0, delta);
            setVelocity(sf::Vector2f(0, getVelocity().y));
            mDeltaP.x = 0;
        }
    }
}



void Mario::die()
{
    mIsDead = true;
    mHitbox.invalidate();
    mAcceleration = {};
    mVelocity = {};
    mInputEnabled = false;
    getTimer().scheduleSeconds(0.5, [&]() {
        mVelocity.y = -10;
        mAcceleration.y = GRAVITY_ACCELERATION;
    });
}
