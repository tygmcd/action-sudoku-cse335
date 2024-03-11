/**
 * @file DeclarationSparty.cpp
 * @author Juan Faure
 */

#include "pch.h"
#include "DeclarationSparty.h"
#include "ItemSparty.h"
#include "Level.h"
#include "Item.h"
#include "Game.h"
using namespace std;

/// String location of the images
const wxString ImageDirectory = "images/";

/**
 * Constructor
 * @param level The level this declaration is a part of
 * @param node The XML node to load data from
 */
DeclarationSparty::DeclarationSparty(Level *level, const wxXmlNode& node) : Declaration(level, node)
{
	XmlLoad(node);
}

/**
 * Load data from XML
 * @param node The XML node to load data from
 */
void DeclarationSparty::XmlLoad(const wxXmlNode& node)
{
	// loading in the front
	node.GetAttribute("front", "0").ToInt(&mFront);

	// loading in head pivot angle value and x,y coordinates
	node.GetAttribute("head-pivot-angle", "0.0").ToDouble(&mHeadPivotAngle);
	node.GetAttribute("head-pivot-x", "0").ToInt(&mHeadPivotX);

	node.GetAttribute("head-pivot-y", "0").ToInt(&mHeadPivotY);

	// loading in mouth pivot angle value and x,y coordinates
	node.GetAttribute("mouth-pivot-angle", "0").ToDouble(&mMouthPivotAngle);
	node.GetAttribute("mouth-pivot-x", "0").ToInt(&mMouthPivotX);
	node.GetAttribute("mouth-pivot-y", "0").ToInt(&mMouthPivotY);

	// loading in target x and target y
	node.GetAttribute("target-x", "0").ToInt(&mTargetX);
	node.GetAttribute("target-y", "0").ToInt(&mTargetY);



	//Load image filename. Image 2 will always be the bottom part.
	wxString imageFilename = node.GetAttribute(L"image", L"INVALID");
	if (imageFilename == "INVALID")
	{
		imageFilename = node.GetAttribute(L"image2", L"INVALID");
	}

	// Load image
	mMouthImage = make_unique<wxImage>(ImageDirectory+imageFilename, wxBITMAP_TYPE_ANY);
	mMouthBitmap = make_unique<wxBitmap>(*mMouthImage);

}


/**
 * Create value that will be able to make the ItemSparty connected to declaration,
 * will be easier to call in Game.
 * @param node The XML node to load data from
 * @return shared pointer to new Item
 */
std::shared_ptr<Item> DeclarationSparty::Create(wxXmlNode& node)
{
    std::shared_ptr<ItemSparty> sparty = std::make_shared<ItemSparty>(GetLevel()->GetGame(),this, node);
    GetLevel()->GetGame()->SetSparty(sparty);
	return std::make_shared<ItemSparty>(GetLevel()->GetGame(),this, node);
}