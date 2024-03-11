/**
 * @file ItemTest.cpp
 * @author Connor Blackmer
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Game.h>
#include <ItemDigit.h>

/** Mock class for testing the class Item */
class DeclarationMock : public Declaration
{
public:
    DeclarationMock(Level* level,  const wxXmlNode& node) : Declaration(level, node) {}
    void Accept(DeclarationVisitor* visitor) {}
    std::shared_ptr<Item> Create(wxXmlNode& node) {return nullptr;};
};
class ItemMock : public Item {
public:
    ItemMock(Game *game, DeclarationMock *dec, wxXmlNode& node) : Item(game, dec, node) {}
    void Accept(ItemVisitor* visitor) {}
};

TEST(ItemTest, Construct) {
    Game game;
    Level level(&game);
    wxXmlNode node;

    // Add image attribute with random image to silence warning
    node.AddAttribute(L"image", L"1b.png");

    DeclarationMock dec(&level, node);
    ItemMock item(&game, &dec, node);
}

TEST(ItemTest, SettersNGetters){
    Game game;
    Level level(&game);
    wxXmlNode node;

    // Add image attribute with random image to silence warning
    node.AddAttribute(L"image", L"1b.png");

    DeclarationMock dec(&level, node);
    ItemMock item(&game, &dec, node);

    // Test initial values
    ASSERT_NEAR(0, item.GetX(), 0.0001);
    ASSERT_NEAR(0, item.GetY(), 0.0001);

    // Test SetLocation, GetX, and GetY
    item.SetLocation(20.5, 53.6);
    ASSERT_NEAR(20.5, item.GetX(), 0.0001);
    ASSERT_NEAR(53.6, item.GetY(), 0.0001);

    // Test SetLocation with other values
    item.SetLocation(-102.4, -2);
    ASSERT_NEAR(-102.4, item.GetX(), 0.0001);
    ASSERT_NEAR(-2, item.GetY(), 0.0001);
}

