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
    EXPECT_EQ(mario->getLeft(), 10);
    EXPECT_EQ(mario->getTop(), 50);

    std::unique_ptr<Pipe> pipe(new Pipe(gSpriteMaker->pipeSprite, {15, 70}));
    EXPECT_EQ(pipe->getLeft(), 15);
    EXPECT_EQ(pipe->getTop(), 70);

    std::unique_ptr<Goomba> goomba(
            new Goomba(gSpriteMaker->goombaSprite, {10, 50}));
    EXPECT_EQ(goomba->getLeft(), 10);
    EXPECT_EQ(goomba->getTop(), 50);
}

TEST(EntityTest, CanGetPositionsOfEntityBoundaries)
{
    // Mario is 16x16 pixels
    std::unique_ptr<Mario> mario(
            new Mario(gSpriteMaker->marioSprite, {20, 50}));
    EXPECT_EQ(mario->getTop(), 50);
    EXPECT_EQ(mario->getBottom(), 66);
    EXPECT_EQ(mario->getLeft(), 20);
    EXPECT_EQ(mario->getRight(), 36);
}

TEST(EntityTest, CanGetPositionOfHitboxBoundaries)
{
    std::unique_ptr<Mario> mario(
            new Mario(gSpriteMaker->marioSprite, {20, 50}));
    const auto hitbox = mario->getHitbox();
    EXPECT_EQ(hitbox.getLeft(), 24);
    EXPECT_EQ(hitbox.getRight(), 32);
    EXPECT_EQ(hitbox.getTop(), 55);
    EXPECT_EQ(hitbox.getBottom(), 66);

}
