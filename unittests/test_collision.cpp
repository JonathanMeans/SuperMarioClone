#include <gtest/gtest.h>
#include "Entity.h"
#include "Utils.h"
#include "file_util.h"

// class FallableStub : public Entity
//{
//    size_t mX;
//    size_t mY;
//
// public:
//    size_t getY() const override
//    {
//        return mY;
//    }
//
//    size_t getX() const override
//    {
//        return mX;
//    }
//
//    size_t getHeight() const override
//    {
//        return 16;
//    }
//
//    void setPosition(size_t x, size_t y) override
//    {
//        mY = y;
//        mX = x;
//    }
//};
//
// class FallableTest : public ::testing::Test
//{
// protected:
//    FallableStub fallable;
//
//    void SetUp() override
//    {
//        fallable.setPosition(100, 100);
//        fallable.setVelocity(sf::Vector2f(100, 100));
//    }
//};
//
// TEST_F(FallableTest, CollidedWithGround)
//{
//    EXPECT_TRUE(fallable.collideWithGround(20));
//    EXPECT_EQ(fallable.getVelocity(), sf::Vector2f(100, 0));
//    EXPECT_EQ(fallable.getY(), 4);
//}
//
// TEST_F(FallableTest, DidNotCollideWithGround)
//{
//    EXPECT_FALSE(fallable.collideWithGround(150));
//}
//
// TEST_F(FallableTest, UpdatePosition)
//{
//    fallable.setAcceleration(sf::Vector2f(10, 15));
//    fallable.updatePosition();
//    EXPECT_EQ(fallable.getX(), 210);
//    EXPECT_EQ(fallable.getY(), 215);
//}
//
// TEST_F(FallableTest, UpdatePositionLimitedByMaxVelocity)
//{
//    fallable.setAcceleration(sf::Vector2f(10, 15));
//    fallable.setVelocity(sf::Vector2f(100, 105));
//    fallable.setMaxVelocity(105);
//    fallable.updatePosition();
//    EXPECT_EQ(fallable.getX(), 205);
//}

TEST(Utils, IsOnRightOf)
{
    // point is left of line
    EXPECT_TRUE(Utils::IsOnRight(sf::Vector2f(0, 100),
                                 sf::Vector2f(0, 0),
                                 sf::Vector2f(-100, 0)));
    // point is right of line
    EXPECT_FALSE(Utils::IsOnRight(sf::Vector2f(0, 100),
                                  sf::Vector2f(0, 0),
                                  sf::Vector2f(100, 0)));
    // point is above the line
    EXPECT_TRUE(Utils::IsOnRight(sf::Vector2f(100, 0),
                                 sf::Vector2f(-100, 0),
                                 sf::Vector2f(0, 100)));
    // point is below the line
    EXPECT_FALSE(Utils::IsOnRight(sf::Vector2f(100, 0),
                                  sf::Vector2f(-100, 0),
                                  sf::Vector2f(0, -100)));
}

TEST(Utils, IsOnLeftOf)
{
    // point is left of line
    EXPECT_FALSE(Utils::IsOnLeft(sf::Vector2f(0, 100),
                                 sf::Vector2f(0, 0),
                                 sf::Vector2f(-100, 0)));
    // point is right of line
    EXPECT_TRUE(Utils::IsOnLeft(sf::Vector2f(0, 100),
                                sf::Vector2f(0, 0),
                                sf::Vector2f(100, 0)));
    // point is above the line
    EXPECT_FALSE(Utils::IsOnLeft(sf::Vector2f(100, 0),
                                 sf::Vector2f(-100, 0),
                                 sf::Vector2f(0, 100)));
    // point is below the line
    EXPECT_TRUE(Utils::IsOnLeft(sf::Vector2f(100, 0),
                                sf::Vector2f(-100, 0),
                                sf::Vector2f(0, -100)));
}

TEST(Utils, IsCollinear)
{
    // point not on line
    EXPECT_FALSE(Utils::IsCollinear(sf::Vector2f(0, 100),
                                    sf::Vector2f(0, 0),
                                    sf::Vector2f(-100, 0)));
    EXPECT_FALSE(Utils::IsCollinear(sf::Vector2f(0, 100),
                                    sf::Vector2f(0, 0),
                                    sf::Vector2f(100, 0)));
    EXPECT_FALSE(Utils::IsCollinear(sf::Vector2f(100, 0),
                                    sf::Vector2f(-100, 0),
                                    sf::Vector2f(0, 100)));
    EXPECT_FALSE(Utils::IsCollinear(sf::Vector2f(100, 0),
                                    sf::Vector2f(-100, 0),
                                    sf::Vector2f(0, -100)));

    // point is on line
    EXPECT_TRUE(Utils::IsCollinear(sf::Vector2f(100, 0),
                                   sf::Vector2f(-100, 0),
                                   sf::Vector2f(0, 0)));
    EXPECT_TRUE(Utils::IsCollinear(sf::Vector2f(100, 0),
                                   sf::Vector2f(-100, 0),
                                   sf::Vector2f(200, 0)));
}

TEST(Utils, IsIntersecting)
{
    EXPECT_TRUE(Utils::IsIntersecting(sf::Vector2f(0, 100),
                                      sf::Vector2f(0, 0),
                                      sf::Vector2f(-100, 0),
                                      sf::Vector2f(100, 0)));
    EXPECT_FALSE(Utils::IsIntersecting(sf::Vector2f(0, 100),
                                       sf::Vector2f(0, 0),
                                       sf::Vector2f(100, 0),
                                       sf::Vector2f(200, 0)));
    EXPECT_FALSE(Utils::IsIntersecting(sf::Vector2f(0, 100),
                                       sf::Vector2f(0, 0),
                                       sf::Vector2f(-100, 0),
                                       sf::Vector2f(-200, 0)));
    EXPECT_TRUE(Utils::IsIntersecting(sf::Vector2f(0, 100),
                                      sf::Vector2f(0, 0),
                                      sf::Vector2f(100, 0),
                                      sf::Vector2f(-100, 0)));

    // collinear lines
    EXPECT_FALSE(Utils::IsIntersecting(sf::Vector2f(100, 0),
                                       sf::Vector2f(-100, 0),
                                       sf::Vector2f(200, 0),
                                       sf::Vector2f(300, 0)));
    EXPECT_TRUE(Utils::IsIntersecting(sf::Vector2f(100, 0),
                                      sf::Vector2f(-100, 0),
                                      sf::Vector2f(200, 0),
                                      sf::Vector2f(-300, 0)));
}

TEST(Utils, IntersectingEdgeCases)
{
    const sf::Vector2f lineOneStart(152, 104);
    const sf::Vector2f lineOneEnd(154, 104);
    const sf::Vector2f lineTwoStart(150, 104);
    const sf::Vector2f lineTwoEnd(166, 104);
    EXPECT_TRUE(Utils::IsIntersecting(
            lineOneStart, lineOneEnd, lineTwoStart, lineTwoEnd));
}

// TEST(Utils, Area2)
//{
//    //point is to the left
//    EXPECT_GT(Utils::Area2(sf::Vector2f(0, 100), sf::Vector2f(0, 0),
//    sf::Vector2f(-100, 0)), 0);
//    //point is to the right
//    EXPECT_FLOAT_EQ(Utils::Area2(sf::Vector2f(0, 100), sf::Vector2f(0, 0),
//    sf::Vector2f(100, 0)), 0);
//    //point is above (left) //point below (right)
//    EXPECT_FLOAT_EQ(Utils::Area2(sf::Vector2f(100, 0), sf::Vector2f(-100, 0),
//    sf::Vector2f(0, 100)), 0);
//    //on the same line and intersecting
//    EXPECT_FLOAT_EQ(Utils::Area2(sf::Vector2f(100, 0), sf::Vector2f(-100, 0),
//    sf::Vector2f(0, 0)), 0);
//    //on the same line, not intersecting
//    EXPECT_FLOAT_EQ(Utils::Area2(sf::Vector2f(100, 0), sf::Vector2f(-100, 0),
//    sf::Vector2f(200, 0)), 0);
//}
