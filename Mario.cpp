#include "Mario.h"
#include "Animation.h"

#include <iostream>
#include "SFML/Graphics.hpp"

Mario::Mario() :
//    mSpriteIndex(0),
//    mTicksPerFrame(2),
//    mRemainingTicsThisFrame(2),
//    mJumpingIndex(0),
//    mJumpingRemainingTicsThisFrame(2),
//    mJumpingTicksPerFrame(2),
    mActiveSprite(nullptr)
{
    if (!mTexture.loadFromFile("../resources/Mario & Luigi.png"))
    {
        std::cerr << "Error Loading Texture";
    }

    // Walking
//    const size_t NUM_SPRITES = 4;
//    mWalkingSprites.resize(NUM_SPRITES);
//
//    for (size_t ii = 0; ii < NUM_SPRITES; ++ii)
//    {
//        static const size_t X_OFFSET = 17;
//        mWalkingSprites[ii].setTexture(mTexture);
//        mWalkingSprites[ii].setTextureRect(
//                sf::IntRect(80 + (X_OFFSET * ii), 34, 16, 16));
//        mWalkingSprites[ii].scale(3, 3);
//        mWalkingSprites[ii].setPosition(100, 100);
//    }

    // Load Jumping Animation
//    const size_t NUM_JUMPING_SPRITES = 2;
//    mJumpingSprites.resize(NUM_JUMPING_SPRITES);
//    for (size_t ii = 0; ii < NUM_JUMPING_SPRITES; ++ii)
//    {
//        static const size_t X_OFFSET = 17;
//        const size_t INITIAL_OFFSET = 80 + X_OFFSET * NUM_SPRITES;
//        mJumpingSprites[ii].setTexture(mTexture);
//        mJumpingSprites[ii].setTextureRect(
//                sf::IntRect(INITIAL_OFFSET + (X_OFFSET * ii), 34, 16, 16));
//        mJumpingSprites[ii].scale(3, 3);
//        mJumpingSprites[ii].setPosition(100, 100);
//    }

    walkingAnimation.load(AnimationType::WALKING, 100, 100, mTexture);
    jumpingAnimation.load(AnimationType::JUMPING, 100, 100, mTexture);
    standingAnimation.load(AnimationType::STANDING, 100, 100, mTexture);
    mActiveSprite = standingAnimation.getActiveSprite();
}

void Mario::draw(sf::RenderWindow& window)
{
    window.draw(*mActiveSprite);
}

void Mario::setPosition(size_t x, size_t y)
{
    walkingAnimation.setPosition(x, y);
    jumpingAnimation.setPosition(x, y);
    standingAnimation.setPosition(x, y);
}

size_t Mario::getX() const
{
    return mActiveSprite->getPosition().x;
//    return mWalkingSprites[mSpriteIndex].getPosition().x;
}

size_t Mario::getY() const
{
    return mActiveSprite->getPosition().y;
//    return mWalkingSprites[mSpriteIndex].getPosition().y;
}

void Mario::walk()
{
    mActiveSprite = walkingAnimation.processAction();
//    --mRemainingTicsThisFrame;
//    if (mRemainingTicsThisFrame == 0)
//    {
//        ++mSpriteIndex;
//        if (mSpriteIndex >= mWalkingSprites.size())
//            mSpriteIndex = 0;
//        mRemainingTicsThisFrame = mTicksPerFrame;
//    }
//    mActiveSprite = &mWalkingSprites[mSpriteIndex];
}

void Mario::stopWalking()
{
//    mSpriteIndex = 0;
//    mRemainingTicsThisFrame = mTicksPerFrame;
    mActiveSprite = standingAnimation.processAction();;
}

void Mario::jump()
{
    mActiveSprite = jumpingAnimation.processAction();
//    --mJumpingRemainingTicsThisFrame;
//    if (mJumpingRemainingTicsThisFrame == 0)
//    {
//        ++mJumpingIndex;
//        if (mJumpingIndex >= mJumpingSprites.size())
//            mJumpingIndex = mJumpingSprites.size() - 1;
//        mJumpingRemainingTicsThisFrame = mJumpingTicksPerFrame;
//    }
//    mActiveSprite = &mJumpingSprites[mJumpingIndex];
}
