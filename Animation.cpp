#include "Animation.h"

#include <iostream>
#include <utility>

#include "Event.h"
#include "Level.h"

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
                     size_t ticsPerFrame,
                     const std::string& name) :
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
    mName(name),
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
        if (fireEventAndReturnTrueIfFinished())
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

bool Animation::fireEventAndReturnTrueIfFinished() const
{
    const auto result = mSpriteIndex == mActionRectangles.size() - 1;
    if (result && !mName.empty() && !mRepeat)
    {
        addEvent(Event::constructAnimationCompleted(mName));
    }
    return result;
}

size_t Animation::getSpriteIndex() const
{
    return mSpriteIndex;
}

size_t Animation::xOffsetForCurrentFrame(size_t frameIndex) const
{
    return mXOffset + ((mWidth + mBorderSize) * frameIndex);
}

void Animation::setActionRectangles(
        const std::vector<sf::IntRect>& actionRectangles)
{
    mActionRectangles = actionRectangles;
    mSpriteIndex = 0;
}

sf::IntRect Animation::getCurrentFrame() const
{
    return mActionRectangles[mSpriteIndex];
}

std::vector<sf::IntRect> Animation::generateActionRectangles() const
{
    std::vector<sf::IntRect> rectangles;
    rectangles.reserve(mNumRect);
    for (size_t ii = 0; ii < mNumRect; ++ii)
    {
        rectangles.emplace_back(xOffsetForCurrentFrame(ii),
                                mYOffset,
                                mWidth,
                                mHeight);
    }
    return rectangles;
}

void Animation::switchPalette(const sf::Vector2f& offset,
                              const sf::Vector2f& size)
{
    mXOffset = offset.x;
    mYOffset = offset.y;
    mWidth = size.x;
    mHeight = size.y;
    mActionRectangles = generateActionRectangles();
}
