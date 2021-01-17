#include <Mario.h>
#include <SpriteMaker.h>
#include <gtest/gtest.h>
#include "Hitbox.h"

extern SpriteMaker* gSpriteMaker;

TEST(Hitbox, InvalidateHitbox)
{
    std::unique_ptr<Mario> mario(
            new Mario(gSpriteMaker->marioSprite, {20, 50}));
    Hitbox hitbox(mario->getHitbox());
    hitbox.invalidate();
    EXPECT_EQ(hitbox.mSize.x, 0);
    EXPECT_EQ(hitbox.mSize.y, 0);
    EXPECT_EQ(hitbox.mUpperLeftOffset.x, -10000.f);
    EXPECT_EQ(hitbox.mUpperLeftOffset.y, -10000.f);
}