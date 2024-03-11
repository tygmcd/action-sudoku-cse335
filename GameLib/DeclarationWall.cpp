/**
 * @file DeclarationWall.cpp
 * @author Connor Blackmer
 */

#include "pch.h"
#include "DeclarationWall.h"
#include "Item.h"
#include "ItemWall.h"
#include "Level.h"

/**
 * Constructor
 * @param level The level this declaration is a part of
 * @param node The XML node to load data from
 */
DeclarationWall::DeclarationWall(Level *level, const wxXmlNode& node) : Declaration(level, node)
{

}

/**
 * Create value that will be able to make the ItemBackground connected to declaration,
 * will be easier to call in Game.
 * @param node The XML node to load data from
 * @return shared pointer to new Item
 */
std::shared_ptr<Item> DeclarationWall::Create(wxXmlNode& node)
{
    return std::make_shared<ItemWall>(GetLevel()->GetGame(),this, node);
}

