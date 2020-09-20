#include <gtest/gtest.h>
#include "Fallable.h"
#include "file_util.h"

class FallableStub : public Fallable
{
    sf::Vector2f mVelocity;
    sf::Vector2f mAcceleration;
    size_t mX;
    size_t mY;

public:
    sf::Vector2f getVelocity() const
    {
        return mVelocity;
    }

    sf::Vector2f getAcceleration() const override
    {
        return mAcceleration;
    }

    size_t getY() const
    {
        return mY;
    }

    size_t getX() const
    {
        return mX;
    }

    size_t getHeight() const
    {
        return 16;
    }

    void setVelocity(const sf::Vector2f& newVelocity)
    {
        mVelocity = newVelocity;
    }

    void setPosition(size_t x, size_t y)
    {
        mY = y;
        mX = x;
    }

    void setAcceleration(const sf::Vector2f& newAcceleration) override
    {
        mAcceleration = newAcceleration;
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
    EXPECT_EQ(fallable.getY(), 205);
}