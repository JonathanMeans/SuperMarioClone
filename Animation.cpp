#include "Animation.h"

#include <utility>

Animation::Animation() = default;

Animation::Animation(sf::Sprite& activeSprite, std::vector<sf::IntRect> actionRectangles,
                     bool repeat) :
    mRemainingTicsThisFrame(2),
    mTicsPerFrame(2),
    mSpriteIndex(0),
    mRepeat(repeat),
    mActionRectangles(std::move(actionRectangles)),
    mActiveSprite(&activeSprite)
{
};

/*
 * TODO: Consider builder pattern, e.g.
 * AnimationBuilder().repeatingAnimation(num_frames=4).withOffset(xOffset,
 * yOffset).withRectWidth(16).andRepeat().build(sprite);
 */
void Animation::load(AnimationType type, sf::Sprite& activeSprite)
{
    mSpriteIndex = 0;
    mTicsPerFrame = 2;
    mRemainingTicsThisFrame = 2;
    mActiveSprite = &activeSprite;
    mRepeat = true;

    switch (type)
    {
    case AnimationType::WALKING:
        generateRectangles(4, 80, 34, 16, 1, 16);
        break;
    case AnimationType::JUMPING:
        generateRectangles(2, 148, 34, 16, 1, 16);
        mRepeat = false;
        break;
    case AnimationType::STANDING:
        generateStaticAnimation(80, 34, 16, 16);
        break;

    case AnimationType::BIG_WALKING:
        generateRectangles(4, 80, 1, 32, 1, 16);
        break;
    case AnimationType ::BIG_JUMPING:
        generateRectangles(2, 148, 1, 32, 1, 16);
        mRepeat = false;
        break;
    case AnimationType::BIG_STANDING:
        generateStaticAnimation(80, 1, 16, 32);
        break;

    case AnimationType::GOOMBA_WALKING:
        generateRectangles(2, 0, 16, 16, 0, 16);
        mTicsPerFrame = 4;
        mRemainingTicsThisFrame = 4;
        break;

    case AnimationType::GOOMBA_DEATH:
        generateRectangles(1, 32, 16, 16, 0, 16);
        break;

    case AnimationType::MARIO_DEATH:
        generateRectangles(1, 182, 34, 16, 0, 16);
        break;

    case AnimationType::PIPE:
        generateStaticAnimation(0, 129, 32, 32);
        break;

    case AnimationType::BLOCK:
        generateStaticAnimation(0, 0, 16, 16);
    }
}

void Animation::generateStaticAnimation(size_t xOffset,
                                        size_t yOffset,
                                        size_t width,
                                        size_t height)
{
    generateRectangles(1, xOffset, yOffset, height, 0, width);
}

void Animation::generateRectangles(size_t numRectangles,
                                   size_t xOffset,
                                   size_t yOffset,
                                   size_t rectHeight,
                                   size_t frameBorder,
                                   size_t rectWidth)
{

    mActionRectangles.resize(numRectangles);
    for (size_t ii = 0; ii < numRectangles; ++ii)
    {
        mActionRectangles[ii] =
                sf::IntRect(xOffset + ((rectWidth + frameBorder) * ii),
                            yOffset,
                            rectWidth,
                            rectHeight);
    }

    mActiveSprite->setTextureRect(mActionRectangles[0]);
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
