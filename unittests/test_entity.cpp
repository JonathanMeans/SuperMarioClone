#include <SpriteMaker.h>
#include <entities/Goomba.h>
#include <entities/Pipe.h>
#include <file_util.h>
#include <gtest/gtest.h>
#include "entities/Mario.h"

extern SpriteMaker* gSpriteMaker;

TEST(EntityTest, CanConstructEntitiesWithPosition)
{
    std::unique_ptr<Mario> mario(
            new Mario(gSpriteMaker->playerTexture, {10, 50}));
    EXPECT_EQ(mario->getLeft(), 10);
    EXPECT_EQ(mario->getTop(), 50);

    std::unique_ptr<Pipe> pipe(
            new Pipe(gSpriteMaker->inanimateObjectTexture, {15, 70}));
    EXPECT_EQ(pipe->getLeft(), 15);
    EXPECT_EQ(pipe->getTop(), 70);

    std::unique_ptr<Goomba> goomba(
            new Goomba(gSpriteMaker->enemyTexture, {10, 50}));
    EXPECT_EQ(goomba->getLeft(), 10);
    EXPECT_EQ(goomba->getTop(), 50);
}

TEST(EntityTest, CanGetPositionsOfEntityBoundaries)
{
    // Mario is 16x16 pixels
    std::unique_ptr<Mario> mario(
            new Mario(gSpriteMaker->playerTexture, {20, 50}));
    EXPECT_EQ(mario->getTop(), 50);
    EXPECT_EQ(mario->getBottom(), 66);
    EXPECT_EQ(mario->getLeft(), 20);
    EXPECT_EQ(mario->getRight(), 36);
}

TEST(EntityTest, CanGetPositionOfHitboxBoundaries)
{
    std::unique_ptr<Mario> mario(
            new Mario(gSpriteMaker->playerTexture, {20, 50}));
    const auto hitbox = mario->getHitbox(EntityType::GROUND);
    EXPECT_EQ(hitbox.getLeft(), 20);
    EXPECT_EQ(hitbox.getRight(), 36);
    EXPECT_EQ(hitbox.getTop(), 50);
    EXPECT_EQ(hitbox.getBottom(), 66);
}
