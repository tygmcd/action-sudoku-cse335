/**
 * @file DeclarationDigit.cpp
 * @author Juan Faure
 */

#include "pch.h"
#include "DeclarationDigit.h"
#include "ItemDigit.h"
#include "Game.h"
#include "Level.h"

/**
 * Constructor
 * @param level The level this declaration is a part of
 * @param node The XML node to load data from
 */
DeclarationDigit :: DeclarationDigit(Level* level, const wxXmlNode& node) : DeclarationNumber(level, node)
{

}

/**
 * Create value that will be able to make the ItemSparty connected to declaration,
 * will be easier to call in Game.
 * @param node The XML node to load data from
 * @return shared ptr to new Item
 */
std::shared_ptr<Item> DeclarationDigit::Create(wxXmlNode& node)
{
    return std::make_shared<ItemDigit>(GetLevel()->GetGame(),this, node);
}