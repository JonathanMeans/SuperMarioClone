#ifndef SUPERMARIOBROS_ANIMATIONBUILDER_H
#define SUPERMARIOBROS_ANIMATIONBUILDER_H

#include "Animation.h"

class AnimationBuilder
{
public:
    AnimationBuilder();
    Animation build(sf::Sprite& sprite);
    AnimationBuilder withOffset(size_t xOffset, size_t yOffset);
    AnimationBuilder withRectSize(size_t width, size_t height);
    AnimationBuilder withNumRect(size_t numRect);
    AnimationBuilder withFrameBorder(size_t borderSize);
    AnimationBuilder andRepeat();
    AnimationBuilder withTicsPerFrame(size_t ticsPerFrame);

private:
    size_t mXOffset;
    size_t mYOffset;
    size_t mWidth;
    size_t mHeight;
    size_t mNumRect;
    size_t mBorderSize;
    bool mRepeat;
    size_t mTicsPerFrame;

};

#endif  // SUPERMARIOBROS_ANIMATIONBUILDER_H
