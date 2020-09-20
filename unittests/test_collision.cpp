#include <gtest/gtest.h>
#include "Fallable.h"
#include "file_util.h"

class FallableStub : public Fallable
{
    size_t mX;
    size_t mY;

public:
    size_t getY() const override
    {
        return mY;
    }

    size_t getX() const override
    {
        return mX;
    }

    size_t getHeight() const override
    {
        return 16;
    }

    void setPosition(size_t x, size_t y) override
    {
        mY = y;
        mX = x;
    }
};

class FallableTest : public ::testing::Test
{
protected:
    FallableStub fallable;

    void SetUp() override
    {
        fallable.setPosition(100, 100);
        fallable.setVelocity(sf::Vector2f(100, 100));
    }
};

TEST_F(FallableTest, CollidedWithGround)
{
    EXPECT_TRUE(fallable.collideWithGround(20));
    EXPECT_EQ(fallable.getVelocity(), sf::Vector2f(100, 0));
    EXPECT_EQ(fallable.getY(), 4);
}

TEST_F(FallableTest, DidNotCollideWithGround)
{
    EXPECT_FALSE(fallable.collideWithGround(150));
}

TEST_F(FallableTest, UpdatePosition)
{
    fallable.setAcceleration(sf::Vector2f(10, 15));
    fallable.updatePosition();
    EXPECT_EQ(fallable.getX(), 210);
    EXPECT_EQ(fallable.getY(), 215);
}

TEST_F(FallableTest, UpdatePositionLimitedByMaxVelocity)
{
    fallable.setAcceleration(sf::Vector2f(10, 15));
    fallable.setVelocity(sf::Vector2f(100, 105));
    fallable.setMaxVelocity(105);
    fallable.updatePosition();
    EXPECT_EQ(fallable.getX(), 205);
}