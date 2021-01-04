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
    EXPECT_EQ(mario->getX(), 10);
    EXPECT_EQ(mario->getY(), 50);

    std::unique_ptr<Pipe> pipe(new Pipe(gSpriteMaker->pipeSprite, {15, 70}));
    EXPECT_EQ(pipe->getX(), 15);
    EXPECT_EQ(pipe->getY(), 70);

    std::unique_ptr<Goomba> goomba(
            new Goomba(gSpriteMaker->goombaSprite, {10, 50}));
    EXPECT_EQ(goomba->getX(), 10);
    EXPECT_EQ(goomba->getY(), 50);
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
