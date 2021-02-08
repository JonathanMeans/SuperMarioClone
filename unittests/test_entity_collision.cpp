#include <gtest/gtest.h>
#include "Goomba.h"
#include "Level.h"
#include "Mario.h"
#include "Pipe.h"
#include "SpriteMaker.h"
#include "file_util.h"

SpriteMaker* gSpriteMaker;

namespace
{
class EntityCollisionTest : public ::testing::Test
{
protected:
    Mario* mario{};

    EntityCollisionTest() = default;

    void SetUp() override
    {
        mario = new Mario(gSpriteMaker->marioSprite, {30, 100});
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
        mario->mDeltaP = {};
        mario->updatePosition();
        mario->collideWithGround(GROUND_HEIGHT);
    }
    EXPECT_EQ(0.f, mario->getBottom());
}

TEST_F(EntityCollisionTest, MarioCanWalkOnPipe)
{
    std::unique_ptr<Mario> mario(
            new Mario(gSpriteMaker->marioSprite, {0, 100}));
    std::unique_ptr<Entity> pipe(new Pipe(gSpriteMaker->pipeSprite, {0, 200}));
    // TODO: Better interface
    std::vector<Entity*> pipes;
    pipes.emplace_back(pipe.get());

    EXPECT_EQ(116.f, mario->getBottom());

    Level level(std::move(mario), pipes);
    for (int i = 0; i < 100; ++i)
    {
        level.executeFrame({});
    }
    EXPECT_EQ(200.f, level.getMario().getBottom());

    // move left two frames
    /*
    auto leftAcceleration = mario->getAcceleration();
    leftAcceleration.x = -1;
    mario->setAcceleration(leftAcceleration);
    for (int i = 0; i < 2; ++i)
    {
        mario->updatePosition();
        mario->collideWithEnemy(pipes);

        // Reset mDeltaP
        mario->mDeltaP.x = 0;
        mario->mDeltaP.y = 0;
    }

    // verify we're still on top of pipe
    EXPECT_EQ(200.f, mario->getBottom());
    EXPECT_GT(mario->getRight(), 0.f);
     */
}

int main(int argc, char** argv)
{
    std::cout << "Running main() from gtest_main.cc\n";
    ::testing::GTEST_FLAG(output) = "xml:hello.xml";
    testing::InitGoogleTest(&argc, argv);
    gSpriteMaker = new SpriteMaker(findRootDirectory(argv[0]) + "resources/");
    return RUN_ALL_TESTS();
}