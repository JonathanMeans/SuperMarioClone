#include "Mario.h"
#include <AnimationBuilder.h>
#include <cassert>
#include "Animation.h"
#include "Hitbox.h"
#include "Timer.h"

Mario::Mario(const sf::Texture& texture, const sf::Vector2f& position) :
    Entity(texture,
           16,
           16,
           Hitbox({12, 11}, {2, 5}),
           EntityType::SMALL_MARIO,
           position,
           2.f),
    smallHitbox(this->mMarioCollisionHitbox),
    largeHitbox({12, 23}, {2, 9}),
    mForm(MarioForm::SMALL_MARIO),
    mJumping(false),
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
    sf::Rect smallRect = sf::IntRect(80, 34, 16, 16);
    sf::Rect mediumRect = sf::IntRect(335, 1, 16, 32);
    sf::Rect largeRect = sf::IntRect(80, 1, 16, 32);
    std::vector<sf::IntRect> growingAnimationRectangles = {smallRect,
                                                           mediumRect,
                                                           smallRect,
                                                           mediumRect,
                                                           smallRect,
                                                           mediumRect,
                                                           largeRect,
                                                           smallRect,
                                                           mediumRect,
                                                           largeRect,
                                                           smallRect,
                                                           largeRect};
    growingAnimation =
            AnimationBuilder()
                    .withNonContiguousRect(growingAnimationRectangles)
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

bool Mario::isGrowing() const
{
    return mActiveAnimation == &growingAnimation;
}

void Mario::setAnimationFromState()
{
    if (isGrowing() && !mActiveAnimation->finished())
        return;

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
            mActiveAnimation = &growingAnimation;
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

EntityType Mario::getType() const
{
    switch (mForm)
    {
    case MarioForm::BIG_MARIO:
        return EntityType::BIG_MARIO;
    case MarioForm::SMALL_MARIO:
        return EntityType::SMALL_MARIO;
    }
    throw std::runtime_error("Unhandled form in Mario::getType()");
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
            terminate();
        }
        else
        {
            addPositionDelta(0, -5);
        }
    }
    else if (collision.entityType == EntityType::MUSHROOM)
    {
        assert(mForm == MarioForm::SMALL_MARIO);
        setForm(MarioForm::BIG_MARIO);
    }
    else
    {
        // We're not colliding with an enemy, so we want the sprite hitbox
        const auto& hitbox = getHitbox(collision.entityType);
        if (collision.side == EntitySide::BOTTOM)
        {
            clampY(hitbox.getBottom(), collision.yIntersection);
            const auto currentVelocity = getVelocity();
            setVelocity(sf::Vector2f(currentVelocity.x, 0));
            setJumping(false);
        }
        else if (collision.side == EntitySide::TOP)
        {
            clampY(hitbox.getTop(), collision.yIntersection);
            setVelocity(sf::Vector2f(getVelocity().x, 0));
            mAcceleration.y = GRAVITY_ACCELERATION;
            mDeltaP.y = 0;
        }
        else if (collision.side == EntitySide::RIGHT)
        {
            clampX(hitbox.getRight(), collision.xIntersection);
            setVelocity(sf::Vector2f(0, getVelocity().y));
            mAcceleration.x = 0;
        }
        else if (collision.side == EntitySide::LEFT)
        {
            clampX(hitbox.getLeft(), collision.xIntersection);
            setVelocity(sf::Vector2f(0, getVelocity().y));
            mAcceleration.x = 0;
        }
    }
}

void Mario::terminate()
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

bool Mario::isJumping() const
{
    return mJumping;
}
