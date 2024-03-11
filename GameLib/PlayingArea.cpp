/**
 * @file PlayingArea.cpp
 * @author Tyler McDonald
 */

#include "pch.h"
#include "PlayingArea.h"
#include "ItemBackground.h"
#include "ItemDigitVisitor.h"

/// Constant rows for the master list
int rows = 9;

/// Constant columns for the master list
int cols = 9;

/**
 * Constructor
 */
PlayingArea::PlayingArea()
{
	InitializeMasterList();
}

/**
 * Draws playing area itself
 * @param graphics graphics context used
 */
void PlayingArea::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
}

/**
 * Adds an item to the playing area
 * @param item Item object to be added
 */
void PlayingArea::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}


/**
 * Test an x,y click location to see if it clicked
 * on some item in the GameView.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> PlayingArea::HitTest(int x, int y)
{
	for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}

	return  nullptr;
}

/**
 * Test an x,y location to see if Sparty can eat
 * some item in the GameView.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we ate or nullptr if none.
*/
std::shared_ptr<Item> PlayingArea::SpartyEatTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
    {
        if ((*i)->CanEat(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}

/**
 * Test an x,y location to see if Sparty can headbutt
 * some item in the GameView.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we headbutted or nullptr if none.
*/
std::shared_ptr<Item> PlayingArea::SpartyHeadbuttTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
    {

        if ((*i)->CanHeadbutt(x, y))
        {
            return *i;
        }

    }

    return  nullptr;
}



/**
 * Update the PlayingArea
 * @param elapsed Time since last update
 */
void PlayingArea::Update(double elapsed)
{
    for (auto item : mItems)
    {
        item->Update(elapsed);
    }
}

/**
 * Accept a visitor for the collection of items
 * @param visitor The visitor for the collection
 */
void PlayingArea::Accept(ItemVisitor* visitor)
{
    for (const auto& item : mItems)
    {
        item->Accept(visitor);
    }
}

/**
 * Clears PlayingArea
 */
void PlayingArea::Clear()
{
    mItems.clear();

    InitializeMasterList();
}

/**
 * Removes an Item from PlayingArea (must be eatable)
 * @param i Item to remove
 */
void PlayingArea::Remove(std::shared_ptr<Item> i)
{

    for (auto item : mItems)
    {
        auto loc = find(begin(mItems), end(mItems), i);
        if (loc != end(mItems))
        {
            mItems.erase(loc);
            break;
        }
    }
}

/**
 * Initializes the list of occupied board cells to all false values
 */
void PlayingArea::InitializeMasterList()
{
    //Clear the matrix
    mMasterList.clear();

    // Initialize the matrix with -1 values (representing an empty cell)
    for (int i = 0; i < rows; i++) {
        std::vector<int> row;
        for (int j = 0; j < cols; j++) {
            row.push_back(-1);
        }
        mMasterList.push_back(row);
    }
}


