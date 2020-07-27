#include "Animation.h"

#include <cstdlib>

Animation::Animation() = default;

void Animation::load(AnimationType type, size_t initialX, size_t initialY, const sf::Texture& texture)
{
    mX = initialX;
    mY = initialY;
    mSpriteIndex = 0;
    mTicsPerFrame = 2;
    mRemainingTicsThisFrame = 2;
    mActiveSprite = nullptr;
    repeat = true;
    if (type == AnimationType::WALKING)
    {
        generateSprites(4, 80, texture);
    } else if (type == AnimationType::JUMPING)
    {
        generateSprites(2, 148, texture);
        repeat = false;
    } else if (type == AnimationType::STANDING)
    {
        generateSprites(1, 80, texture);
    }
}

void Animation::generateSprites(const size_t numSprites, size_t initialOffset, const sf::Texture& texture)
{
    const size_t NUM_SPRITES = numSprites;
    mActionSprites.resize(NUM_SPRITES);
    for (size_t ii = 0; ii < NUM_SPRITES; ++ii)
    {
        static const size_t X_OFFSET = 17;
        mActionSprites[ii].setTexture(texture);
        mActionSprites[ii].setTextureRect(
                sf::IntRect(initialOffset + (X_OFFSET * ii), 34, 16, 16));
        mActionSprites[ii].scale(3, 3);
        mActionSprites[ii].setPosition(100, 100);
    }

    mActiveSprite = &mActionSprites[0];
}

sf::Sprite* Animation::processAction()
{
    --mRemainingTicsThisFrame;
    if (mRemainingTicsThisFrame == 0)
    {
        ++mSpriteIndex;
        if (mSpriteIndex >= mActionSprites.size()) {
            if (repeat)
            {
                mSpriteIndex = 0;
            } else {
                mSpriteIndex = mActionSprites.size() - 1;
            }
        }
        mRemainingTicsThisFrame = mTicsPerFrame;
    }
    mActiveSprite = &mActionSprites[mSpriteIndex];
    return mActiveSprite;
};

void Animation::setPosition(size_t x, size_t y)
{
    for (auto& sprite : mActionSprites)
        sprite.setPosition(x, y);
}

sf::Sprite* Animation::getActiveSprite()
{
    return mActiveSprite;
}




