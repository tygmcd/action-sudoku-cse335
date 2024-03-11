/**
 * @file NumberTest.cpp
 * @author Walker McDonald
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <DeclarationNumber.h>
#include <ItemDigit.h>
#include <Game.h>
#include <Level.h>
#include <GetAllDigitsVisitor.h>

TEST(NumberTest, ValueVisitors)
{
    //Load level 0
    Game game;
    Level level = Level(&game);
    level.Load("levels/level0.xml");

    //Use the get all digits visitor
    std::shared_ptr<GetAllDigitsVisitor> digitVisitor = std::make_shared<GetAllDigitsVisitor>();
    game.GetPlayingArea()->Accept(digitVisitor.get());

    //Get a digit from the get all digits visitor
    ItemDigit* digit = digitVisitor->PopDigitOfValue(1);
    ASSERT_NE(digit, nullptr);

    //Make sure the obtained digit has the correct value
    ASSERT_EQ(digit->GetValue(), 1);
}