#include <gtest/gtest.h>
#include "Animation.h"

TEST(Animation, InitializeSpriteIndex)
{
    Animation animation;
    EXPECT_EQ(0, animation.getSpriteIndex());
}

TEST(Animation, JumpingSpriteIndexIncreasesWithStep)
{
    Animation animation;
    auto sprite = std::make_shared<sf::Sprite>();
    animation.load(AnimationType::JUMPING, sprite);

    animation.processAction();
    animation.processAction();
    EXPECT_EQ(1, animation.getSpriteIndex());

    animation.processAction();
    animation.processAction();
    EXPECT_EQ(1, animation.getSpriteIndex());
}

TEST(Animation, WalkingSpriteIndexIncreasesWithStep)
{
    Animation animation;
    auto sprite = std::make_shared<sf::Sprite>();
    animation.load(AnimationType::WALKING, sprite);

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
