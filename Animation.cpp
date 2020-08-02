#include "Animation.h"

#include <iostream>

Animation::Animation() = default;

void Animation::load(AnimationType type, const std::shared_ptr<sf::Sprite>& activeSprite)
{

    if (!mTexture.loadFromFile("../resources/Mario & Luigi.png"))
    {
        std::cerr << "Error Loading Texture";
    }
    mTexture.setSmooth(false);
    mSpriteIndex = 0;
    mTicsPerFrame = 2;
    mRemainingTicsThisFrame = 2;
    mActiveSprite = activeSprite;
    mActiveSprite->setTexture(mTexture);
    repeat = true;
    if (type == AnimationType::WALKING)
    {
        generateRectangles(4, 80);
    } else if (type == AnimationType::JUMPING)
    {
        generateRectangles(2, 148);
        repeat = false;
    } else if (type == AnimationType::STANDING)
    {
        generateRectangles(1, 80);
    }
}

void Animation::generateRectangles(size_t numRectangles, size_t initialOffset)
{
    const size_t NUM_RECTANGLES = numRectangles;
    mActionRectangles.resize(NUM_RECTANGLES);
    for (size_t ii = 0; ii < NUM_RECTANGLES; ++ii)
    {
        static const size_t X_OFFSET = 17;
        mActionRectangles[ii] = sf::IntRect(
                initialOffset + (X_OFFSET * ii), 34, 16, 16);
    }

    mActiveSprite->setTextureRect(mActionRectangles[0]);
}

std::shared_ptr<sf::Sprite> Animation::processAction()
{
    --mRemainingTicsThisFrame;
    if (mRemainingTicsThisFrame == 0)
    {
        ++mSpriteIndex;
        if (mSpriteIndex >= mActionRectangles.size()) {
            if (repeat)
            {
                mSpriteIndex = 0;
            } else {
                mSpriteIndex = mActionRectangles.size() - 1;
            }
        }
        mRemainingTicsThisFrame = mTicsPerFrame;
    }
    mActiveSprite->setTextureRect(mActionRectangles[mSpriteIndex]);
    return mActiveSprite;
};

void Animation::setPosition(size_t x, size_t y)
{
    mActiveSprite->setPosition(x, y);
}



