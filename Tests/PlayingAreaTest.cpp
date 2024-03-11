/**
 * @file PlayingAreaTest.cpp
 * @author Juan Faure
 */


#include <pch.h>
#include "gtest/gtest.h"
#include <PlayingArea.h> /// includes the playing area
#include <Game.h> /// Includes Game just in case
#include <ItemTypeCounterVisitor.h>

using namespace std;

class DeclarationMock : public DeclarationSparty
{
public:
    DeclarationMock(Level* level,  const wxXmlNode& node) : DeclarationSparty(level, node) {}
};

TEST(PlayingAreaTest, ItemVisitor){
    Game game;

    std::shared_ptr<ItemTypeCounterVisitor> collectionVisitor = std::make_shared<ItemTypeCounterVisitor>();
    game.GetPlayingArea()->Accept(collectionVisitor.get());

    ASSERT_EQ(collectionVisitor->GetBackgroundCount(), 1);
    ASSERT_EQ(collectionVisitor->GetContainerCount(), 0);
    ASSERT_EQ(collectionVisitor->GetDigitCount(), 53);
    ASSERT_EQ(collectionVisitor->GetGivenCount(), 28);
    ASSERT_EQ(collectionVisitor->GetNumberCount(), 81);
    ASSERT_EQ(collectionVisitor->GetXrayCount(), 1);
}