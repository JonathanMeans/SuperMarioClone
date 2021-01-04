#include <gtest/gtest.h>
#include "Goomba.h"
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
        mario->updatePosition();
        mario->collideWithGround(GROUND_HEIGHT);
        mario->applyDeltaP();
    }
    EXPECT_EQ(0.f, mario->getBottomPosition());
}

TEST_F(EntityCollisionTest, MarioCanWalkOnPipe)
{
    std::unique_ptr<Entity> mario(
            new Mario(gSpriteMaker->marioSprite, {0, 100}));
    std::unique_ptr<Entity> pipe(new Pipe(gSpriteMaker->pipeSprite));
    pipe->setPosition(0, 200);
    // TODO: Better interface
    std::vector<Entity*> pipes;
    pipes.emplace_back(pipe.get());
    EXPECT_EQ(116.f, mario->getBottomPosition());
    for (int i = 0; i < 100; ++i)
    {
        if (i == 4)
            int x = 5;
        mario->updatePosition();
        mario->collideWithEnemy(pipes);
        mario->applyDeltaP();
    }
    EXPECT_EQ(200.f, mario->getBottomPosition());

    // move left two frames
    auto leftAcceleration = mario->getAcceleration();
    leftAcceleration.x = -1;
    mario->setAcceleration(leftAcceleration);
    for (int i = 0; i < 1; ++i)
    {
        mario->mDeltaP = {};
        mario->updatePosition();
        mario->collideWithEnemy(pipes);
        mario->applyDeltaP();
    }

    // verify we're still on top of pipe
    EXPECT_EQ(200.f, mario->getBottomPosition());
    EXPECT_LE(mario->getX(), 0.f);
}

int main(int argc, char** argv)
{
    std::cout << "Running main() from gtest_main.cc\n";
    ::testing::GTEST_FLAG(output) = "xml:hello.xml";
    testing::InitGoogleTest(&argc, argv);
    gSpriteMaker = new SpriteMaker(findRootDirectory(argv[0]) + "resources/");
    return RUN_ALL_TESTS();
}