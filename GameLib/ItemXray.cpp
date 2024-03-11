/**
 * @file ItemXray.cpp
 * @author Connor Blackmer
 */

#include "pch.h"
#include "ItemXray.h"
#include "Item.h"
#include "ItemDigit.h"
#include "ItemNumber.h"
#include "ItemNumberVisitor.h"

/// Constant for placing digits randomly
const double Threshold = 25;

/**
 * node implemented Item constructor
 * @param game pointer to the game the object is a part of
 * @param dec pointer to the declaration iof this specific object
 * @param node which will be how we will be loading in the item info from the level
 */
ItemXray::ItemXray(Game *game,DeclarationXray *dec,wxXmlNode& node): Item(game,dec,node)
{
    mDeclaration = dec;
    XmlLoad(node);

    // Seed the random number generator
    std::random_device rd;
    mRandom.seed(rd());
}
/**
 * Draws x-ray on the playing area
 * @param graphics graphics context used
 */
void ItemXray::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->DrawBitmap(*mDeclaration->GetBitmap(),GetX(),GetY(),mDeclaration->GetWidth(),mDeclaration->GetHeight());

    if (!mContainedDigits.empty())
    {
        for (auto item : mContainedDigits)
        {
            graphics->DrawBitmap(*item->GetDeclaration()->GetBitmap(),item->GetX(),item->GetY(),item->GetWidth()/1.6,item->GetHeight()/1.6);
        }
    }
}

/**
 * Adds a Item to Xray
 * @param item shared pointer to Item
 */
void ItemXray::Add(std::shared_ptr<Item> item)
{
    mContainedDigits.push_back(item);
    std::uniform_real_distribution<> distributionX(GetX()+10, GetX() + 95);
    std::uniform_real_distribution<> distributionY(GetY()+10, GetY() + 95);
    double setX = distributionX(this->GetRandom());
    double setY = distributionY(this->GetRandom());

    while (!IsValidLocation(setX, setY))
    {
        setX = distributionX(this->GetRandom());
        setY = distributionY(this->GetRandom());
    }

    item->SetLocation(setX, setY);
}

/**
 * spits out an item of first instance if it hase the same number
 * @param targetNumber value to find and remove from xray
 * @return shared pointer to Item
 */

std::shared_ptr<Item> ItemXray::Spit(int targetNumber)
{

    ItemNumberVisitor visitor;
	std::shared_ptr<Item> number = nullptr; // values that we will be returning

	if(!mContainedDigits.empty())
	{
		for(auto item : mContainedDigits)
		{
			(*item).Accept(&visitor);
			if(visitor.GetCurrentValue() == targetNumber)
			{
				number = item; // assign that value

				// delete the values from the vector
				auto loc = find(begin(mContainedDigits), end(mContainedDigits), item);
				if(loc != end(mContainedDigits))
				{
					mContainedDigits.erase(loc);
					break;
				}
			}

		}
	}
	return number;
}
/**
 * Checks if a number is in the contained digits vector
 * @param targetNumber value to find
 * @return true if in vector
 */

bool ItemXray::NumInListChecker(int targetNumber)
{
    ItemNumberVisitor visitor;

    if(!mContainedDigits.empty())
    {
        for(auto item : mContainedDigits)
        {
            (*item).Accept(&visitor);
            if(visitor.GetCurrentValue() == targetNumber)
            {
                return true;
            }
        }
    }
    return false;
}


/**
 * Uses distance formula to see if an Item is placed in a valid location (overlapping or not)
 * @param x new x location
 * @param y new y location
 * @return bool indicating if item is in valid location
 */
bool ItemXray::IsValidLocation(double x, double y)
{

    for (auto item : mContainedDigits)
    {
        double distance  = sqrt(pow(x - item->GetX(), 2) + pow(y- item->GetY(), 2));
        if (distance < Threshold)
        {
            return false;
        }
    }

    return true;
}


