#include <gtest/gtest.h>
#include "Utils.h"
#include "file_util.h"


TEST(Utils, IsOnRightOf)
{
    // point is left of line
    EXPECT_TRUE(Utils::IsOnRight(sf::Vector2f(0, 100),
                                 sf::Vector2f(0, 0),
                                 sf::Vector2f(-100, 0)));
    // point is right of line
    EXPECT_FALSE(Utils::IsOnRight(sf::Vector2f(0, 100),
                                  sf::Vector2f(0, 0),
                                  sf::Vector2f(100, 0)));
    // point is above the line
    EXPECT_TRUE(Utils::IsOnRight(sf::Vector2f(100, 0),
                                 sf::Vector2f(-100, 0),
                                 sf::Vector2f(0, 100)));
    // point is below the line
    EXPECT_FALSE(Utils::IsOnRight(sf::Vector2f(100, 0),
                                  sf::Vector2f(-100, 0),
                                  sf::Vector2f(0, -100)));
}

TEST(Utils, IsOnLeftOf)
{
    // point is left of line
    EXPECT_FALSE(Utils::IsOnLeft(sf::Vector2f(0, 100),
                                 sf::Vector2f(0, 0),
                                 sf::Vector2f(-100, 0)));
    // point is right of line
    EXPECT_TRUE(Utils::IsOnLeft(sf::Vector2f(0, 100),
                                sf::Vector2f(0, 0),
                                sf::Vector2f(100, 0)));
    // point is above the line
    EXPECT_FALSE(Utils::IsOnLeft(sf::Vector2f(100, 0),
                                 sf::Vector2f(-100, 0),
                                 sf::Vector2f(0, 100)));
    // point is below the line
    EXPECT_TRUE(Utils::IsOnLeft(sf::Vector2f(100, 0),
                                sf::Vector2f(-100, 0),
                                sf::Vector2f(0, -100)));
}

TEST(Utils, IsCollinear)
{
    // point not on line
    EXPECT_FALSE(Utils::IsCollinear(sf::Vector2f(0, 100),
                                    sf::Vector2f(0, 0),
                                    sf::Vector2f(-100, 0)));
    EXPECT_FALSE(Utils::IsCollinear(sf::Vector2f(0, 100),
                                    sf::Vector2f(0, 0),
                                    sf::Vector2f(100, 0)));
    EXPECT_FALSE(Utils::IsCollinear(sf::Vector2f(100, 0),
                                    sf::Vector2f(-100, 0),
                                    sf::Vector2f(0, 100)));
    EXPECT_FALSE(Utils::IsCollinear(sf::Vector2f(100, 0),
                                    sf::Vector2f(-100, 0),
                                    sf::Vector2f(0, -100)));

    // point is on line
    EXPECT_TRUE(Utils::IsCollinear(sf::Vector2f(100, 0),
                                   sf::Vector2f(-100, 0),
                                   sf::Vector2f(0, 0)));
    EXPECT_TRUE(Utils::IsCollinear(sf::Vector2f(100, 0),
                                   sf::Vector2f(-100, 0),
                                   sf::Vector2f(200, 0)));
}

TEST(Utils, IsIntersecting)
{
    EXPECT_TRUE(Utils::IsIntersecting(sf::Vector2f(0, 100),
                                      sf::Vector2f(0, 0),
                                      sf::Vector2f(-100, 0),
                                      sf::Vector2f(100, 0)));
    EXPECT_FALSE(Utils::IsIntersecting(sf::Vector2f(0, 100),
                                       sf::Vector2f(0, 0),
                                       sf::Vector2f(100, 0),
                                       sf::Vector2f(200, 0)));
    EXPECT_FALSE(Utils::IsIntersecting(sf::Vector2f(0, 100),
                                       sf::Vector2f(0, 0),
                                       sf::Vector2f(-100, 0),
                                       sf::Vector2f(-200, 0)));
    EXPECT_TRUE(Utils::IsIntersecting(sf::Vector2f(0, 100),
                                      sf::Vector2f(0, 0),
                                      sf::Vector2f(100, 0),
                                      sf::Vector2f(-100, 0)));

    // collinear lines
    EXPECT_FALSE(Utils::IsIntersecting(sf::Vector2f(100, 0),
                                       sf::Vector2f(-100, 0),
                                       sf::Vector2f(200, 0),
                                       sf::Vector2f(300, 0)));
    EXPECT_TRUE(Utils::IsIntersecting(sf::Vector2f(100, 0),
                                      sf::Vector2f(-100, 0),
                                      sf::Vector2f(200, 0),
                                      sf::Vector2f(-300, 0)));
}

TEST(Utils, IntersectingEdgeCases)
{
    const sf::Vector2f lineOneStart(152, 104);
    const sf::Vector2f lineOneEnd(154, 104);
    const sf::Vector2f lineTwoStart(150, 104);
    const sf::Vector2f lineTwoEnd(166, 104);
    EXPECT_TRUE(Utils::IsIntersecting(
            lineOneStart, lineOneEnd, lineTwoStart, lineTwoEnd));
}

TEST(Utils, MovingLeftOnTopOfEntityShouldNotHitLeftSide)
{
    const sf::Vector2f moverStart(3, 190);
    const sf::Vector2f moverEnd(2, 191);
    const sf::Vector2f lineStart(0, -800);
    const sf::Vector2f lineEnd(0, 1200);
    EXPECT_TRUE(!Utils::IsIntersecting(
            moverStart, moverEnd, lineStart, lineEnd));
}

