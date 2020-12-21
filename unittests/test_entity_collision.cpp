#include <gtest/gtest.h>
#include "Goomba.h"
#include "Mario.h"
#include "Pipe.h"
#include "SpriteMaker.h"
#include "file_util.h"

namespace {

    SpriteMaker* gSpriteMaker;

    class EntityCollisionTest: public ::testing::Test {
    protected:

        Mario * mario{};

        EntityCollisionTest() = default;

        void SetUp() override
        {
            mario = new Mario(gSpriteMaker->marioSprite);
        }

        void TearDown() override
        {
            delete mario;
        }

        ~EntityCollisionTest() override = default;

    };
}

TEST_F(EntityCollisionTest, MarioFallsToGround)
{
    const float GROUND_HEIGHT = 0.f;
    // Mario's initial height is 100
    // TODO: Set this from caller, not Mario Ctor
    for (int i = 0; i < 100; ++i)
    {
        mario->updatePosition();
        if (i == 2)
        {
            int x = 0;
        }
        mario->collideWithGround(GROUND_HEIGHT);
        mario->applyDeltaP();
    }
    EXPECT_EQ(0.f, mario->getBottomPosition());
}

int main(int argc, char **argv) {
    std::cout << "Running main() from gtest_main.cc\n";
    ::testing::GTEST_FLAG(output) = "xml:hello.xml";
    testing::InitGoogleTest(&argc, argv);
    gSpriteMaker = new SpriteMaker(findRootDirectory(argv[0]) + "resources/");
    return RUN_ALL_TESTS();
}