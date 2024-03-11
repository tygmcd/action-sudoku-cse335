/**
 * @file ItemNumber.cpp
 * @author Connor Blackmer
 */

#include "pch.h"
#include "ItemNumber.h"
#include "NumberDeclarationValueVisitor.h"
#include "Game.h"
#include "ItemNumberVisitor.h"


/**
 * node implemented Item constructor
 * @param game pointer to the game the object is a part of
 * @param dec pointer to the declaration iof this specific object
 * @param node which will be how we will be loading in the item info from the level
 */
ItemNumber::ItemNumber(Game *game,DeclarationNumber *dec,wxXmlNode& node) : Item(game,dec,node)
{
    mNumberDeclaration = dec;
}

/**
* Get the value of this number
* @return The value of this number
*/
int ItemNumber::GetValue()
{
    Declaration* declaration = GetDeclaration();
    std::shared_ptr<NumberDeclarationValueVisitor> visitor = std::make_shared<NumberDeclarationValueVisitor>();
    declaration->Accept(visitor.get());
    return visitor->GetValue();
}

/**
 * Sets the item's location
 * @param x The new location's x coordinate in virtual pixels
 * @param y The new location's y coordinate in virtual pixels
 */
void ItemNumber::SetLocation(double x, double y)
{
    //If the digit was previously within the bounds of the sudoku grid
    if (mInSudokuGrid)
    {
        int cellX = GetGame()->GetLevel()->PositionXToCellColumn(GetX());
        int cellY = GetGame()->GetLevel()->PositionYToCellRow(GetY());
        if (cellX!=-1 && cellY!=-1)
            GetGame()->GetPlayingArea()->SetCellValue(cellX, cellY, -1);
        mInSudokuGrid = false;
    }

    //Upcall
    Item::SetLocation(x, y);

    //Check whether the digit is now within the bounds of the sudoku grid
    int cellX = GetGame()->GetLevel()->PositionXToCellColumn(GetX());
    int cellY = GetGame()->GetLevel()->PositionYToCellRow(GetY());
    if (cellX!=-1 && cellY!=-1)
    {
        //Get this number's value
        std::shared_ptr<ItemNumberVisitor> visitor = std::make_shared<ItemNumberVisitor>();
        Accept(visitor.get());
        int value = visitor->GetCurrentValue();

        //Update the sudoku grid
        GetGame()->GetPlayingArea()->SetCellValue(cellX, cellY, value);
        mInSudokuGrid = true;
    }
}

