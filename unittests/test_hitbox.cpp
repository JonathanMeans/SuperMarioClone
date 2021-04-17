#include <SpriteMaker.h>
#include <entities/Mario.h>
#include <gtest/gtest.h>
#include "Hitbox.h"

extern SpriteMaker* gSpriteMaker;

namespace
{
class HitboxTest : public ::testing::Test
{
protected:
    Mario* mario{};
    Hitbox* hitbox{};

    HitboxTest() = default;

    void SetUp() override
    {
        mario = new Mario(gSpriteMaker->playerTexture, {20, 50});
        hitbox = new Hitbox(mario->getHitbox(EntityType::GROUND));
    }

    void TearDown() override
    {
        delete mario;
        delete hitbox;
    }

    ~HitboxTest() override = default;
};
}

TEST_F(HitboxTest, InvalidateHitbox)
{
    hitbox->invalidate();
    EXPECT_EQ(hitbox->mSize.x, 0);
    EXPECT_EQ(hitbox->mSize.y, 0);
    EXPECT_EQ(hitbox->mUpperLeftOffset.x, -10000.f);
    EXPECT_EQ(hitbox->mUpperLeftOffset.y, -10000.f);
}
