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
        mario->collideWithGround(GROUND_HEIGHT);
        mario->applyDeltaP();
    }
    EXPECT_EQ(0.f, mario->getBottomPosition());
}

TEST_F(EntityCollisionTest, MarioCanWalkOnPipe)
{
    std::unique_ptr<Entity> mario(gSpriteMaker->getMario().atPosition(0, 100).build());
    std::unique_ptr<Entity> pipe(gSpriteMaker->getPipe().atPosition(0, 0).build());
    // TODO: Better interface
    std::vector<Entity*> pipes;
    pipes.emplace_back(pipe.get());
    for (int i = 0; i < 100; ++i)
    {
        mario->updatePosition();
        mario->collideWithEnemy(pipes);
        mario->applyDeltaP();
    }
    EXPECT_EQ(0.f, mario->getBottomPosition());

    // move left two frames
    auto leftAcceleration = mario->getAcceleration();
    leftAcceleration.x = -1;
    mario->setAcceleration(leftAcceleration);
    for (int i = 0; i < 2; ++i)
    {
        mario->mDeltaP = {};
        mario->updatePosition();
        mario->collideWithEnemy(pipes);
        mario->applyDeltaP();
    }

    // verify we're still on top of pipe
    EXPECT_EQ(0.f, mario->getBottomPosition());
    EXPECT_LE(mario->getX(), 0.f);
}

int main(int argc, char **argv) {
    std::cout << "Running main() from gtest_main.cc\n";
    ::testing::GTEST_FLAG(output) = "xml:hello.xml";
    testing::InitGoogleTest(&argc, argv);
    gSpriteMaker = new SpriteMaker(findRootDirectory(argv[0]) + "resources/");
    return RUN_ALL_TESTS();
}