/**
 * @file LevelTest.cpp
 * @author Walker McDonald
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>
#include <Game.h>
#include <Declaration.h>
#include <NumberDeclarationValueVisitor.h>

using namespace std;

TEST(LevelTest, Construct){
    Game game;
    Level level = Level(&game);
}

TEST(LevelTest, LoadBase){
    Game game;
    Level level = Level(&game);
    level.Load("levels/level0.xml");

    ASSERT_EQ(level.GetWidth(), 20 * 48);
    ASSERT_EQ(level.GetHeight(), 15 * 48);
}

TEST(LevelTest, LoadGame){
    Game game;
    Level level = Level(&game);
    level.Load("levels/level0.xml");

    ASSERT_EQ(level.GetBoardColumn(), 6);
    ASSERT_EQ(level.GetBoardRow(), 3);

    ASSERT_EQ(level.GetSolution(0), 3);
    ASSERT_EQ(level.GetSolution(10), 5);
    ASSERT_EQ(level.GetSolution(100), -1);
}

TEST(LevelTest, LoadDeclaration){
    Game game;
    Level level = Level(&game);
    level.Load("levels/level0.xml");

    //Test a digit declaration
    auto digit = level.GetDeclaration("i365");
    ASSERT_NE(digit, nullptr);

    ASSERT_EQ(digit->GetWidth(), 48);
    ASSERT_EQ(digit->GetHeight(), 48);

    //Test a given declaration
    auto given = level.GetDeclaration("i368");
    ASSERT_NE(given, nullptr);

    ASSERT_EQ(given->GetWidth(), 48);
    ASSERT_EQ(given->GetHeight(), 48);

    //Test a sparty declaration
    auto sparty = level.GetDeclaration("i382");
    ASSERT_NE(sparty, nullptr);

    ASSERT_EQ(sparty->GetWidth(), 96);
    ASSERT_EQ(sparty->GetHeight(), 96);

    //Test a background declaration
    auto background = level.GetDeclaration("i389");
    ASSERT_NE(background, nullptr);

    ASSERT_EQ(background->GetWidth(), 960);
    ASSERT_EQ(background->GetHeight(), 720);

    //Test an xray declaration
    auto xray = level.GetDeclaration("i384");
    ASSERT_NE(xray, nullptr);

    ASSERT_EQ(xray->GetWidth(), 144);
    ASSERT_EQ(xray->GetHeight(), 144);
}

TEST(LevelTest, LoadNumberDeclaration){
    Game game;
    Level level = Level(&game);
    level.Load("levels/level0.xml");

    //Test a digit declaration
    auto digit = level.GetDeclaration("i365");
    ASSERT_NE(digit, nullptr);

    std::shared_ptr<NumberDeclarationValueVisitor> digitVisitor = std::make_shared<NumberDeclarationValueVisitor>();
    digit->Accept(digitVisitor.get());
    ASSERT_EQ(digitVisitor->GetValue(), 1);

    //Test a given declaration
    auto given = level.GetDeclaration("i368");
    ASSERT_NE(given, nullptr);

    std::shared_ptr<NumberDeclarationValueVisitor> givenVisitor = std::make_shared<NumberDeclarationValueVisitor>();
    given->Accept(givenVisitor.get());
    ASSERT_EQ(givenVisitor->GetValue(), 3);

    //Test the collection as a whole
    std::shared_ptr<NumberDeclarationValueVisitor> collectionVisitor = std::make_shared<NumberDeclarationValueVisitor>();
    level.Accept(collectionVisitor.get());
    ASSERT_EQ(collectionVisitor->GetValue(), (0+1+2+3+4+5+6+7+8)*2);
}