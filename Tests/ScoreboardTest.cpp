/**
 * @file ScoreboardTest.cpp
 * @author Tyler McDonald
 *
 * Test basic functionality of Scoreboard
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Scoreboard.h>

using namespace std;

TEST(Scoreboard, Construct)
{
    Scoreboard scoreboard;
}

TEST(Scoreboard, IncrementSeconds)
{
    Scoreboard scoreboard;

    scoreboard.IncrementSeconds();
    scoreboard.IncrementSeconds();

    ASSERT_EQ(scoreboard.GetSeconds(), 2);

    scoreboard.IncrementSeconds();

    ASSERT_EQ(scoreboard.GetSeconds(), 3);

}

TEST (Scoreboard, ResetScoreboard)
{
    Scoreboard scoreboard;

    scoreboard.IncrementSeconds();
    scoreboard.IncrementSeconds();
    scoreboard.IncrementSeconds();

    ASSERT_EQ(scoreboard.GetSeconds(), 3);

    scoreboard.ResetScoreboard();

    ASSERT_EQ(scoreboard.GetSeconds(), 0);
}
