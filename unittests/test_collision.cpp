#include <gtest/gtest.h>
#include "Fallable.h"
#include "file_util.h"

class FallableStub : public Fallable
{
    sf::Vector2f mVelocity;
    size_t mX;
    size_t mY;

public:
    sf::Vector2f getVelocity() const
    {
        return mVelocity;
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