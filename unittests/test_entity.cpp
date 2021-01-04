#include <SpriteMaker.h>
#include <file_util.h>
#include <gtest/gtest.h>
#include "Mario.h"

extern SpriteMaker* gSpriteMaker;

namespace
{
class EntityTest : public ::testing::Test
{
protected:
    Mario* mario{};

    EntityTest() = default;

    void SetUp() override
    {
        mario = new Mario(gSpriteMaker->marioSprite, sf::Vector2f{30, 100});
        ;
    }

    void TearDown() override
    {
        delete mario;
    }

    ~EntityTest() override = default;
};
}

TEST_F(EntityTest, EntityPositionAfterRotating)
{
    ASSERT_NE(mario, nullptr);
    EXPECT_EQ(mario->getX(), 30);
}
