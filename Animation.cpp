#include "Animation.h"

#include <utility>

Animation::Animation() = default;

Animation::Animation(sf::Sprite& activeSprite,
                     size_t numRect,
                     size_t xOffset,
                     size_t yOffset,
                     size_t width,
                     size_t height,
                     size_t borderSize,
                     bool repeat,
                     std::vector<sf::IntRect> actionRectangles,
                     size_t ticsPerFrame) :
    mRemainingTicsThisFrame(ticsPerFrame),
    mTicsPerFrame(ticsPerFrame),
    mSpriteIndex(0),
    mNumRect(numRect),
    mXOffset(xOffset),
    mYOffset(yOffset),
    mWidth(width),
    mHeight(height),
    mBorderSize(borderSize),
    mRepeat(repeat),
    mActionRectangles(std::move(actionRectangles)),
    mActiveSprite(&activeSprite)
{

    if (mActionRectangles.empty())
    {
        mActionRectangles = generateActionRectangles();
    }

    mActiveSprite->setTextureRect(mActionRectangles[0]);
}

void Animation::processAction()
{
    --mRemainingTicsThisFrame;
    if (mRemainingTicsThisFrame == 0)
    {
        if (finished())
        {
            if (mRepeat)
            {
                mSpriteIndex = 0;
            }
        }
        else
        {
            ++mSpriteIndex;
        }
        mRemainingTicsThisFrame = mTicsPerFrame;
    }
    mActiveSprite->setTextureRect(mActionRectangles[mSpriteIndex]);
}

bool Animation::finished() const
{
    return mSpriteIndex == mActionRectangles.size() - 1;
}

size_t Animation::getSpriteIndex() const
{
    return mSpriteIndex;
}

std::vector<sf::IntRect> Animation::generateActionRectangles() const
{
        std::vector<sf::IntRect> rectangles;
        rectangles.reserve(mNumRect);
        for (size_t ii = 0; ii < mNumRect; ++ii)
        {
            rectangles.emplace_back(mXOffset + ((mWidth + mBorderSize) * ii),
                                           mYOffset,
                                           mWidth,
                                           mHeight);
        }
        return rectangles;
}

void Animation::switchPalette(const sf::Vector2f& offset, const sf::Vector2f& size) {
    mXOffset = offset.x;
    mYOffset = offset.y;
    mWidth = size.x;
    mHeight = size.y;
    mActionRectangles = generateActionRectangles();
}
