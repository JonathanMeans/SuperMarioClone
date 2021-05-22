#include "Animation.h"

#include <utility>

#include "AnimationBuilder.h"

Animation::Animation() = default;

Animation::Animation(sf::Sprite& activeSprite,
                     std::vector<sf::IntRect> actionRectangles,
                     bool repeat,
                     size_t ticsPerFrame,
                     const std::shared_ptr<AnimationBuilder>& animationBuilder) :
    mRemainingTicsThisFrame(ticsPerFrame),
    mTicsPerFrame(ticsPerFrame),
    mSpriteIndex(0),
    mRepeat(repeat),
    mActionRectangles(std::move(actionRectangles)),
    mActiveSprite(&activeSprite),
    mAnimationBuilder(std::move(animationBuilder))
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

Animation Animation::switchPalette(const sf::Vector2f& offset, const sf::Vector2f& size) {
    mAnimationBuilder->withOffset(offset.x, offset.y);
    mAnimationBuilder->withRectSize(size.x, size.y);
    return mAnimationBuilder->build(*mActiveSprite);
}
