/**
 * @file Item.cpp
 * @author Connor Blackmer
 */

#include "pch.h"
#include "Game.h"
#include "Item.h"

/// Used for eating
const double widthBuffer = 12;



/**
 * node implemented Item constructor
 * @param game pointer to the game the object is a part of
 * @param dec pointer to the declaration iof this specific object
 * @param node which will be how we will be loading in the item info from the level
 */
Item::Item(Game *game, Declaration *dec,wxXmlNode& node): mGame(game), mDeclaration(dec) // <-- clean way to initialize private member variables
{
}


/**
* Destructor
*/
Item::~Item()
{
}

/**
 * Test to see if we hit this object with a mouse.
 * @param x will be the x coordinate
 * @param y will be the y coord
 * @return bool of true if hit.
 */
bool Item::HitTest(int x, int y)
{
	double wid = mDeclaration->GetBitmap()->GetWidth();
	double hit = mDeclaration->GetBitmap()->GetHeight();


	// Make x and y relative to the top-left corner of the bitmap image
	// Subtracting the center makes x, y relative to the image center
	// Adding half the size makes x, y relative to the image top corner
	double testX = x - GetX() + wid / 2;
	double testY = y - GetY() + hit / 2;

	// Test to see if x, y are in the image
	if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
	{
		// We are outside the image
        return false;
	}

	//NOTE: We do not have to test for transparency
	return true;
}


/**
 * Load the Item from XML
 * @param node The XML node to load data from
 */
void Item::XmlLoad(const wxXmlNode& node)
{
    double x;
    double y;

    mID = node.GetAttribute(L"id", L"INVALID");
    node.GetAttribute(L"col", L"INVALID").ToDouble(&x);
    node.GetAttribute(L"row", L"INVALID").ToDouble(&y);

    x = x * mGame->GetLevel()->GetTileHeight();
    y = (y + 1) * mGame->GetLevel()->GetTileHeight() - mDeclaration->GetHeight();
    SetLocation(x, y);
}

/**
 * Checks to see if sparty is in eatable distance on a digit
 * @param spartyX sparty x position
 * @param spartyY sparty y position
 * @return true if sparty can eat
 */
bool Item::CanEat(int spartyX, int spartyY)
{
    double wid = mDeclaration->GetBitmap()->GetWidth();
    double hit = mDeclaration->GetBitmap()->GetHeight();

    // Add one column to Sparty's position for testing
    spartyX = spartyX + GetGame()->GetLevel()->GetTileWidth();
    double halfColumn = (GetGame()->GetLevel()->GetTileWidth()) / 2.0;

    if (spartyX <= GetX() + widthBuffer && spartyX > GetX() - halfColumn &&
        spartyY >= GetY() - hit - halfColumn && spartyY < GetY())
    {
        return true;
    }

    return false;


}

/**
 * Checks to see if sparty is close enough to headbutt
 * @param spartyX sparty x position
 * @param spartyY sparty y position
 * @return true if sparty can butt
 */
bool Item::CanHeadbutt(int spartyX, int spartyY)
{
    double wid = mDeclaration->GetBitmap()->GetWidth();
    double hit = mDeclaration->GetBitmap()->GetHeight();

    // Add one column to Sparty's position for testing
    spartyX = spartyX + GetGame()->GetLevel()->GetTileWidth();
    double column = (GetGame()->GetLevel()->GetTileWidth());

    if (spartyX <= GetX() && spartyX > GetX() - column &&
        spartyY <= GetY() + hit && spartyY > GetY())
    {
        return true;
    }

    return false;


}