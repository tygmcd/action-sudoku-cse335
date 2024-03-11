/**
 * @file ItemContainer.cpp
 * @author Connor Blackmer
 */

#include "pch.h"
#include "ItemContainer.h"


/// Constant for random X position
const double MinPosX = -200;

/// Constant for random X position
const double MaxPosX = 200;

/// Constant for random Y position
const double MinPosY = -200;

/// Constant for random Y position
const double MaxPosY = -150;

/// Constant for placing digits randomly
const double Threshold = 25;


/**
 * node implemented Item constructor
 * @param game pointer to the game the object is a part of
 * @param dec pointer to the declaration iof this specific object
 * @param node which will be how we will be loading in the item info from the level
 */
ItemContainer::ItemContainer(Game *game,DeclarationContainer *dec,wxXmlNode& node): Item(game,dec,node)
{
	mDeclaration = dec;
	XmlLoad(node); // this will use the function within Item to load the specifics for this container

    // Seed the random number generator
    std::random_device rd;
    mRandom.seed(rd());

}
/**
 * Draws container on the playing area
 * @param graphics graphics context used
 */
void ItemContainer::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // comment to commit new changes
	// this is the line of code is from Tyler

    graphics->DrawBitmap(*mDeclaration->GetBitmap(),GetX(),GetY(),mDeclaration->GetWidth(),mDeclaration->GetHeight());
    for (auto digit : mContainedDigits)
    {
        digit->Draw(graphics);
    }

    graphics->DrawBitmap(*mDeclaration->GetContainerBitmap(), GetX(), GetY(),
                         mDeclaration->GetContainerBitmap()->GetWidth(), mDeclaration->GetContainerBitmap()->GetHeight());


}

/**
 * Add item to the Container
 * @param item shared ptr to Item
 */
void ItemContainer::Add(std::shared_ptr<Item> item)
{
    mContainedDigits.push_back(item);
}

/**
 * Move all Items from container to the PlayingArea
 * @param playingArea pointer to PlayingArea object
 */
void ItemContainer::MoveToPlayingArea(std::shared_ptr<PlayingArea> playingArea)
{
    std::uniform_real_distribution<> distributionX(MinPosX, MaxPosX);
    std::uniform_real_distribution<> distributionY(MinPosY, MaxPosY);


    for (auto item : mContainedDigits)
    {
        double setX = item->GetX() + distributionX(this->GetRandom());
        double setY = item->GetY() + distributionY(this->GetRandom());

        while (!IsValidLocation(setX, setY))
        {
            setX = item->GetX() + distributionX(this->GetRandom());
            setY = item->GetY() + distributionY(this->GetRandom());
        }

        item->SetLocation(setX, setY);

        playingArea->Add(item);
    }

    mContainedDigits.clear();
}

/**
 * Uses distance formula to see if an Item is placed in a valid location (overlapping or not)
 * @param x new x location
 * @param y new y location
 * @return bool indicating if item is in valid location
 */
bool ItemContainer::IsValidLocation(double x, double y)
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