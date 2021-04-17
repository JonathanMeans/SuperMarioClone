#include "Mario.h"
#include <AnimationBuilder.h>
#include "Animation.h"
#include "Hitbox.h"
#include "Timer.h"

Mario::Mario(const sf::Texture& texture, const sf::Vector2f& position) :
    Entity(texture,
           16,
           16,
           Hitbox({12, 11}, {2, 5}),
           EntityType::MARIO,
           position,
           2.f),
    smallHitbox(this->mMarioCollisionHitbox),
    largeHitbox({12, 23}, {2, 9}),
    mForm(MarioForm::SMALL_MARIO),
    mJumping(false),
    mFalling(true),
    mIsDead(false)
{
    walkingAnimation = AnimationBuilder()
                               .withOffset(80, 34)
                               .withRectSize(16, 16)
                               .andRepeat()
                               .withNumRect(4)
                               .withFrameBorder(1)
                               .build(mActiveSprite);
    jumpingAnimation = AnimationBuilder()
                               .withOffset(148, 34)
                               .withRectSize(16, 16)
                               .withNumRect(2)
                               .withFrameBorder(1)
                               .build(mActiveSprite);
    standingAnimation =
            AnimationBuilder().withOffset(80, 34).withRectSize(16, 16).build(
                    mActiveSprite);
    deathAnimation =
            AnimationBuilder().withOffset(182, 34).withRectSize(16, 16).build(
                    mActiveSprite);

    bigWalkingAnimation = AnimationBuilder()
                                  .withOffset(80, 1)
                                  .withRectSize(16, 32)
                                  .withNumRect(4)
                                  .withFrameBorder(1)
                                  .andRepeat()
                                  .build(mActiveSprite);
    bigStandingAnimation =
            AnimationBuilder().withOffset(80, 1).withRectSize(16, 32).build(
                    mActiveSprite);
    bigJumpingAnimation = AnimationBuilder()
                                  .withOffset(148, 1)
                                  .withRectSize(16, 32)
                                  .withNumRect(2)
                                  .withFrameBorder(1)
                                  .build(mActiveSprite);

    mActiveAnimation = &standingAnimation;
    mActiveAnimation->processAction();
}

const Hitbox& Mario::getHitbox(EntityType type) const
{
    switch (type)
    {
    case EntityType ::GOOMBA:
        return mMarioCollisionHitbox;
    case EntityType ::PIPE:
        return mMarioCollisionHitbox;
    default:
        return mSpriteBoundsHitbox;
    }
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
            mMarioCollisionHitbox = largeHitbox;
            mSpriteBoundsHitbox = createSpriteBoundsHitbox();
            updateHitboxPositions();
        }
        else if (form == MarioForm::SMALL_MARIO)
        {
            const auto currentY = mActiveSprite.getPosition().y;
            const auto newY = currentY + GRIDBOX_SIZE;
            mActiveSprite.setPosition(mActiveSprite.getPosition().x, newY);
            mActiveAnimation = &standingAnimation;
            mSpriteHeight /= 2;
            mMarioCollisionHitbox = smallHitbox;
            mSpriteBoundsHitbox = createSpriteBoundsHitbox();
            updateHitboxPositions();
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
        // We're not colliding with an enemy, so we want the sprite hitbox
        const auto& hitbox = getHitbox(collision.entityType);
        if (collision.side == EntitySide::BOTTOM)
        {
            auto spriteBottom = hitbox.getBottom();
            auto newSpriteBottom = collision.yIntersection;
            const auto delta = newSpriteBottom - spriteBottom;
            addPositionDelta(0, delta);

            const auto currentVelocity = getVelocity();
            setVelocity(sf::Vector2f(currentVelocity.x, 0));
            setJumping(false);
            mFalling = false;
        }
        else if (collision.side == EntitySide::TOP)
        {
            auto spriteTop = hitbox.getTop();
            auto newSpriteTop = collision.yIntersection;
            const auto delta = newSpriteTop - spriteTop;
            addPositionDelta(0, delta);

            setVelocity(sf::Vector2f(getVelocity().x, 0));
            mFalling = true;
            mAcceleration.y = GRAVITY_ACCELERATION;
            mDeltaP.y = 0;
        }
        else if (collision.side == EntitySide::RIGHT)
        {
            auto spriteRight = hitbox.getRight();
            auto newSpriteRight = collision.xIntersection;
            const auto delta = newSpriteRight - spriteRight;
            addPositionDelta(delta, 0);
            setVelocity(sf::Vector2f(0, getVelocity().y));
            mAcceleration.x = 0;
        }
        else if (collision.side == EntitySide::LEFT)
        {
            auto spriteLeft = hitbox.getLeft();
            auto newSpriteLeft = collision.xIntersection;
            const auto delta = newSpriteLeft - spriteLeft;
            addPositionDelta(delta, 0);
            setVelocity(sf::Vector2f(0, getVelocity().y));
            mAcceleration.x = 0;
        }
    }
}

void Mario::die()
{
    mIsDead = true;
    mMarioCollisionHitbox.invalidate();
    mAcceleration = {};
    mVelocity = {};
    mInputEnabled = false;
    getTimer().scheduleSeconds(0.5, [&]() {
        mVelocity.y = -10;
        mAcceleration.y = GRAVITY_ACCELERATION;
    });
}
