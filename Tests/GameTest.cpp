/**
 * @file GameTest.cpp
 * @author Tyler McDonald
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>
#include <Game.h>

using namespace std;

TEST(GameTest, Construct)
{
    Game game;

    //Make sure required references have been initialized
    ASSERT_NE(game.GetPlayingArea(), nullptr);
    ASSERT_NE(game.GetSparty(), nullptr);
    ASSERT_NE(game.GetLevel(), nullptr);
}



