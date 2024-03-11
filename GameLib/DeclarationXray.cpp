/**
 * @file DeclarationXray.cpp
 * @author Juan Faure
 */

#include "pch.h"
#include "DeclarationXray.h"
#include "ItemXray.h"
#include "Item.h"
#include "Level.h"
#include "Game.h"
using namespace std;

/**
 * Constructor
 * @param level The level this declaration is a part of
 * @param node The XML node to load data from
 */
DeclarationXray::DeclarationXray(Level *level, const wxXmlNode& node) : Declaration(level, node)
{
	// load actual values from the xml
	XmlLoad(node);
}


/**
 * Load the declaration from XML
 * @param node The XML node to load data from
 */
void DeclarationXray::XmlLoad(const wxXmlNode& node)
{
	node.GetAttribute("capacity", "0").ToInt(&mCapacity);
}


/**
 * Create value that will be able to make the ItemSparty connected to declaration,
 * will be easier to call in Game.
 * @param node The XML node to load data from
 * @return shared pointer to new Item
 */
std::shared_ptr<Item> DeclarationXray::Create(wxXmlNode& node)
{
	return std::make_shared<ItemXray>(GetLevel()->GetGame(),this, node);
}
