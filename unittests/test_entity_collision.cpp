#include <gtest/gtest.h>
#include "entities/Goomba.h"
#include "Level.h"
#include "SpriteMaker.h"
#include "entities/Mario.h"
#include "entities/Pipe.h"
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

TEST_F(EntityCollisionTest, MarioCanWalkOnPipe)
{
    // TODO: Better interface
    std::unique_ptr<Mario> mario(
            new Mario(gSpriteMaker->marioSprite, {0, 100}));
    std::unique_ptr<Entity> pipe(new Pipe(gSpriteMaker->pipeSprite, {0, 200}));
    std::vector<std::unique_ptr<Entity>> pipes(1);
    pipes[0] = std::move(pipe);

    EXPECT_EQ(116.f, mario->getBottom());

    Level level(std::move(mario), std::move(pipes));
    for (int i = 0; i < 100; ++i)
    {
        level.executeFrame({});
    }
    EXPECT_EQ(200.f, level.getMario().getBottom());

    // move left two frames
    for (int i = 0; i < 2; ++i)
    {
        KeyboardInput input = {};
        input.left.keyIsDown = true;
        level.executeFrame(input);
    }

    // verify we're still on top of pipe
    EXPECT_EQ(200.f, level.getMario().getBottom());
    EXPECT_GT(level.getMario().getRight(), 0.f);
}

int main(int argc, char** argv)
{
    std::cout << "Running main() from gtest_main.cc\n";
    ::testing::GTEST_FLAG(output) = "xml:hello.xml";
    testing::InitGoogleTest(&argc, argv);
    gSpriteMaker = new SpriteMaker(findRootDirectory(argv[0]) + "resources/");
    return RUN_ALL_TESTS();
}