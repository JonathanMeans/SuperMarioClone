#include <Goomba.h>
#include <Pipe.h>
#include <SpriteMaker.h>
#include <file_util.h>
#include <gtest/gtest.h>
#include "Mario.h"

extern SpriteMaker* gSpriteMaker;

TEST(EntityTest, CanConstructEntitiesWithPosition)
{
    std::unique_ptr<Mario> mario(
            new Mario(gSpriteMaker->marioSprite, {10, 50}));
    EXPECT_EQ(mario->getLeft(), 2);
    EXPECT_EQ(mario->getTop(), 50);

    std::unique_ptr<Pipe> pipe(new Pipe(gSpriteMaker->pipeSprite, {15, 70}));
    EXPECT_EQ(pipe->getLeft(), -1);
    EXPECT_EQ(pipe->getTop(), 70);

    std::unique_ptr<Goomba> goomba(
            new Goomba(gSpriteMaker->goombaSprite, {10, 50}));
    EXPECT_EQ(goomba->getLeft(), 2);
    EXPECT_EQ(goomba->getTop(), 50);
}

TEST(EntityTest, CanGetPositionsOfEntityBoundaries)
{
    // Mario is 16x16 pixels
    std::unique_ptr<Mario> mario(
            new Mario(gSpriteMaker->marioSprite, {20, 50}));
    EXPECT_EQ(mario->getTop(), 50);
    EXPECT_EQ(mario->getBottom(), 66);
    EXPECT_EQ(mario->getLeft(), 12);
    EXPECT_EQ(mario->getRight(), 28);
}
