/**
 * @file DeclarationBackground.cpp
 * @author Juan Faure
 */

#include "pch.h"
#include "DeclarationBackground.h"
#include "Item.h"
#include "ItemBackground.h"
#include "Level.h"
#include "Game.h"


/**
 * Constructor
 * @param level The level this declaration is a part of
 * @param node The XML node to load data from
 */
DeclarationBackground::DeclarationBackground(Level *level, const wxXmlNode& node) : Declaration(level, node)
{

}

/**
 * Creates an item from a wxXmlNode
 * @param node wxXmlNode with item info
 * @return shared ptr to new Item
 */
std::shared_ptr<Item> DeclarationBackground::Create(wxXmlNode& node)
{
	return std::make_shared<ItemBackground>(GetLevel()->GetGame(),this, node);
}

