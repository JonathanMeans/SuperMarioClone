#include "Animation.h"

#include <utility>

Animation::Animation() = default;

Animation::Animation(sf::Sprite& activeSprite,
                     std::vector<sf::IntRect> actionRectangles,
                     bool repeat,
                     size_t ticsPerFrame) :
    mRemainingTicsThisFrame(ticsPerFrame),
    mTicsPerFrame(ticsPerFrame),
    mSpriteIndex(0),
    mRepeat(repeat),
    mActionRectangles(std::move(actionRectangles)),
    mActiveSprite(&activeSprite)
{
}

void Animation::processAction()
{
    --mRemainingTicsThisFrame;
    if (mRemainingTicsThisFrame == 0)
    {
        ++mSpriteIndex;
        if (mSpriteIndex >= mActionRectangles.size())
        {
            if (mRepeat)
            {
                mSpriteIndex = 0;
            }
            else
            {
                mSpriteIndex = mActionRectangles.size() - 1;
            }
        }
        mRemainingTicsThisFrame = mTicsPerFrame;
    }
    mActiveSprite->setTextureRect(mActionRectangles[mSpriteIndex]);
}

size_t Animation::getSpriteIndex() const
{
    return mSpriteIndex;
}
