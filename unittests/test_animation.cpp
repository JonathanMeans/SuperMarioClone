#include <AnimationBuilder.h>
#include <gtest/gtest.h>
#include "Animation.h"

TEST(Animation, InitializeSpriteIndex)
{
    Animation animation;
    EXPECT_EQ(0, animation.getSpriteIndex());
}

TEST(Animation, JumpingSpriteIndexIncreasesWithStep)
{
    sf::Sprite sprite;
    auto animation =
            AnimationBuilder().withTicsPerFrame(2).withNumRect(2).build(sprite);

    animation.processAction();
    animation.processAction();
    EXPECT_EQ(1, animation.getSpriteIndex());

    animation.processAction();
    animation.processAction();
    EXPECT_EQ(1, animation.getSpriteIndex());
}

TEST(Animation, WalkingSpriteIndexIncreasesWithStep)
{
    sf::Sprite sprite;
    auto animation = AnimationBuilder()
                             .withTicsPerFrame(2)
                             .withNumRect(4)
                             .andRepeat()
                             .build(sprite);

    animation.processAction();
    animation.processAction();
    EXPECT_EQ(1, animation.getSpriteIndex());

    animation.processAction();
    animation.processAction();
    EXPECT_EQ(2, animation.getSpriteIndex());

    animation.processAction();
    animation.processAction();
    EXPECT_EQ(3, animation.getSpriteIndex());

    animation.processAction();
    animation.processAction();
    EXPECT_EQ(0, animation.getSpriteIndex());
}
