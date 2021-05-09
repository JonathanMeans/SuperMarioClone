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
