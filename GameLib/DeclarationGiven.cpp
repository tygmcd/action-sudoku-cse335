/**
 * @file DeclarationGiven.cpp
 * @author Juan Faure
 */

#include "pch.h"
#include "DeclarationGiven.h"
#include "ItemGiven.h"
#include "Level.h"
#include "Game.h"

/**
 * Constructor
 * @param level The level this declaration is a part of
 * @param node The XML node to load data from
 */
DeclarationGiven :: DeclarationGiven(Level* level, const wxXmlNode& node) : DeclarationNumber(level, node)
{

}

/**
 * Create value that will be able to make the ItemSparty connected to declaration,
 * will be easier to call in Game.
 * @param node The XML node to load data from
 * @return shared ptr to new Item
 */
std::shared_ptr<Item> DeclarationGiven::Create(wxXmlNode& node)
{
    return std::make_shared<ItemGiven>(GetLevel()->GetGame(),this, node);
}