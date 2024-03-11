/**
 * @file DeclarationContainer.cpp
 * @author Juan Faure
 */

#include "pch.h"
#include "DeclarationContainer.h"
#include  "ItemContainer.h"
#include "Level.h"
#include "Game.h"

using namespace std;

/// String location of the images
const wxString ImageDirectory = "images/";

/**
 * Constructor
 * @param level The level this declaration is a part of
 * @param node The XML node to load data from
 */
DeclarationContainer::DeclarationContainer(Level *level, const wxXmlNode& node) : Declaration(level, node)
{
	XmlLoad(node);
}


/**
 * Load data from XML
 * @param node The XML node to load data from
 */
void DeclarationContainer::XmlLoad(const wxXmlNode& node)
{
	//Load image filename. Image 2 will always be the bottom part.
    wxString imageFilename = node.GetAttribute(L"front", L"INVALID");

	//Load image
	mItemImage = make_unique<wxImage>(ImageDirectory+imageFilename, wxBITMAP_TYPE_ANY);
	mContainerBitMap = make_unique<wxBitmap>(*mItemImage);
}

/**
 * Create value that will be able to make the ItemSparty connected to declaration,
 * will be easier to call in Game.
 * @param node wxXmlNode with item info
 * @return shared ptr to new Item
 */
std::shared_ptr<Item> DeclarationContainer::Create(wxXmlNode& node)
{
    return std::make_shared<ItemContainer>(GetLevel()->GetGame(),this, node);
}