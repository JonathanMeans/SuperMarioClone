#include "Mario.h"
#include "Animation.h"
#include "Hitbox.h"
#include "Utils.h"
#include "Timer.h"

#include <memory>

namespace
{
const Hitbox smallHitbox = Hitbox({8, 11}, {4, 5});
const Hitbox largeHitbox = Hitbox({12, 23}, {2, 8});
const std::vector<EntitySide> SIDES{EntitySide::TOP,
                                    EntitySide::RIGHT,
                                    EntitySide::BOTTOM,
                                    EntitySide::LEFT};
const std::vector<EntityCorner> CORNERS{EntityCorner::UPPER_LEFT,
                                        EntityCorner::UPPER_RIGHT,
                                        EntityCorner::LOWER_RIGHT,
                                        EntityCorner::LOWER_LEFT};
}

Mario::Mario(std::shared_ptr<sf::Sprite>& sprite) :
    Entity(sprite, 16, 16, smallHitbox, 2.f),
    mForm(MarioForm::SMALL_MARIO),
    mJumping(false),
    mIsDead(false)
{
    mActiveSprite->setPosition(100, 100);

    walkingAnimation.load(AnimationType::WALKING, mActiveSprite);
    jumpingAnimation.load(AnimationType::JUMPING, mActiveSprite);
    standingAnimation.load(AnimationType::STANDING, mActiveSprite);
    deathAnimation.load(AnimationType::MARIO_DEATH, mActiveSprite);

    bigWalkingAnimation.load(AnimationType::BIG_WALKING, mActiveSprite);
    bigStandingAnimation.load(AnimationType::BIG_STANDING, mActiveSprite);
    bigJumpingAnimation.load(AnimationType::BIG_JUMPING, mActiveSprite);

    mActiveAnimation = &standingAnimation;
    mActiveAnimation->processAction();

    const auto spriteOrigin = GRIDBOX_SIZE / 2;
    mActiveSprite->setOrigin(spriteOrigin, 0);
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
        mActiveSprite->scale(-1.f, 1.f);
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
            const auto currentY = mActiveSprite->getPosition().y;
            const auto newY = currentY - GRIDBOX_SIZE;
            mActiveSprite->setPosition(mActiveSprite->getPosition().x, newY);
            mActiveAnimation = &bigStandingAnimation;
            mSpriteHeight *= 2;
            mHitbox = largeHitbox;
        }
        else if (form == MarioForm::SMALL_MARIO)
        {
            const auto currentY = mActiveSprite->getPosition().y;
            const auto newY = currentY + GRIDBOX_SIZE;
            mActiveSprite->setPosition(mActiveSprite->getPosition().x, newY);
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

bool Mario::collideWithGround(const size_t groundY)
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
}

bool Mario::collideWithEnemy(std::vector<Entity*>& enemies)
{
    size_t mTopEdge = Mario::getY() + mHitbox.mUpperLeftOffset.y;
    size_t mBottomEdge = mTopEdge + mHitbox.mSize.y;
    size_t mLeftEdge = Mario::getX() + mHitbox.mUpperLeftOffset.x;
    size_t mRightEdge = mLeftEdge + mHitbox.mSize.x;

    for (auto& enemy : enemies)
    {
        size_t eTopEdge = enemy->getY();
        size_t eLeftEdge = enemy->getX();
        size_t eRightEdge = eLeftEdge + enemy->getWidth();
        size_t eBottomEdge = eTopEdge + enemy->getHeight();
        if (mLeftEdge < eRightEdge && mRightEdge > eLeftEdge &&
            mTopEdge < eBottomEdge && mBottomEdge > eTopEdge)
        {
            sf::Vector2f enemyEdge1, enemyEdge2;
            for (const auto& corner : CORNERS)
            {
                sf::Vector2f marioPath1;
                this->getHitboxCorner(corner, marioPath1);
                const sf::Vector2f marioPath2 = marioPath1 + mDeltaP;
                for (const auto& side : SIDES)
                {
                    enemy->getHitboxSide(side, true, enemyEdge1, enemyEdge2);
                    if (Utils::IsIntersecting(
                                marioPath1, marioPath2, enemyEdge1, enemyEdge2))
                    {
                        if (side == EntitySide::TOP)
                        {
                            mDeltaP.y -= 5;
                            enemy->die();
                        }
                        else
                            die();
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Mario::die()
{
    mIsDead = true;
    mHitbox = Hitbox({0.f, 0.f}, {-10000.f, -100000.f});
    mAcceleration = {};
    mVelocity = {};
    mInputEnabled = false;
    getTimer().scheduleSeconds(0.5, [&]() { mVelocity.y = -10; mAcceleration.y = GRAVITY_ACCELERATION;});
}

