#include "AnimationBuilder.h"

AnimationBuilder::AnimationBuilder() :
    mXOffset(-1),
    mYOffset(-1),
    mWidth(-1),
    mHeight(-1),
    mNumRect(1),
    mBorderSize(0),
    mRepeat(false),
    mTicsPerFrame(2)
{
}

AnimationBuilder AnimationBuilder::withOffset(size_t xOffset, size_t yOffset)
{
    mXOffset = xOffset;
    mYOffset = yOffset;
    return *this;
}

AnimationBuilder AnimationBuilder::withRectSize(size_t width, size_t height)
{
    mWidth = width;
    mHeight = height;
    return *this;
}

AnimationBuilder AnimationBuilder::withNumRect(size_t numRect)
{
    mNumRect = numRect;
    return *this;
}

AnimationBuilder AnimationBuilder::withFrameBorder(size_t borderSize)
{
    mBorderSize = borderSize;
    return *this;
}

AnimationBuilder AnimationBuilder::andRepeat()
{
    mRepeat = true;
    return *this;
}

AnimationBuilder AnimationBuilder::withTicsPerFrame(size_t ticsPerFrame)
{
    mTicsPerFrame = ticsPerFrame;
    return *this;
}

AnimationBuilder AnimationBuilder::withNonContiguousRect(
        const std::vector<sf::IntRect>& rectangles)
{
    mRectangles = rectangles;
    return *this;
}

Animation AnimationBuilder::build(sf::Sprite& sprite) const
{
    if (!mRectangles.empty())
    {
        sprite.setTextureRect(mRectangles[0]);
        return Animation(sprite, mRectangles, mRepeat, mTicsPerFrame);
    }

    std::vector<sf::IntRect> mActionRectangles;
    mActionRectangles.resize(mNumRect);
    for (size_t ii = 0; ii < mNumRect; ++ii)
    {
        mActionRectangles[ii] =
                sf::IntRect(mXOffset + ((mWidth + mBorderSize) * ii),
                            mYOffset,
                            mWidth,
                            mHeight);
    }

    sprite.setTextureRect(mActionRectangles[0]);

    return Animation(sprite, mActionRectangles, mRepeat, mTicsPerFrame);
}
