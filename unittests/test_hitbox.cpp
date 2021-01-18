#include <Mario.h>
#include <SpriteMaker.h>
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
        mario = new Mario(gSpriteMaker->marioSprite, {20, 50});
        hitbox = new Hitbox(mario->getHitbox());
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

TEST_F(HitboxTest, GetCorner)
{
    sf::Vector2f points = {};
    hitbox->getCorner(EntityCorner::UPPER_RIGHT, points);
    EXPECT_EQ(points.x, 32);
    EXPECT_EQ(points.y, 55);
    hitbox->getCorner(EntityCorner::UPPER_LEFT, points);
    EXPECT_EQ(points.x, 24);
    EXPECT_EQ(points.y, 55);
    hitbox->getCorner(EntityCorner::LOWER_LEFT, points);
    EXPECT_EQ(points.x, 24);
    EXPECT_EQ(points.y, 66);
    hitbox->getCorner(EntityCorner::LOWER_RIGHT, points);
    EXPECT_EQ(points.x, 32);
    EXPECT_EQ(points.y, 66);
}

TEST_F(HitboxTest, getSide)
{
    sf::Vector2f p1 = {};
    sf::Vector2f p2 = {};
    hitbox->getSide(EntitySide::LEFT, false, p1, p2);
    EXPECT_EQ(p1.x, 24);
    EXPECT_EQ(p1.y, 55);
    EXPECT_EQ(p2.x, 24);
    EXPECT_EQ(p2.y, 66);
    hitbox->getSide(EntitySide::RIGHT, false, p1, p2);
    EXPECT_EQ(p1.x, 32);
    EXPECT_EQ(p1.y, 55);
    EXPECT_EQ(p2.x, 32);
    EXPECT_EQ(p2.y, 66);
    hitbox->getSide(EntitySide::TOP, false, p1, p2);
    EXPECT_EQ(p1.x, 24);
    EXPECT_EQ(p1.y, 55);
    EXPECT_EQ(p2.x, 32);
    EXPECT_EQ(p2.y, 55);
    hitbox->getSide(EntitySide::BOTTOM, false, p1, p2);
    EXPECT_EQ(p1.x, 24);
    EXPECT_EQ(p1.y, 66);
    EXPECT_EQ(p2.x, 32);
    EXPECT_EQ(p2.y, 66);
}
