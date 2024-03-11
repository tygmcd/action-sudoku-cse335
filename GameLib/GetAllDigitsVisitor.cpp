/**
 * @file GetAllDigitsVisitor.cpp
 * @author Walker McDonald
 */

#include "pch.h"
#include "GetAllDigitsVisitor.h"
#include "ItemDigit.h"

/**
 * Visits a digit, adds it to the dictionary if it is not already in the playing area
 * @param digit pointer to ItemDigit
 */
void GetAllDigitsVisitor::VisitDigit(ItemDigit* digit)
{
    //Make sure the digit is not in the sudoku grid
    if (!digit->GetInSudokuGrid())
    {
        //Save the digit to the correct list in the map (key=value)
        int value = digit->GetValue();
        mDigits[value].push_back(digit);
    }
}

/**
 * Pop a digit of the given value from the map
 * @param value The value to get a digit of
 * @return Pointer to the popped digit or nullptr if none
*/
ItemDigit* GetAllDigitsVisitor::PopDigitOfValue(int value)
{
    //No remaining digits of this value
    if (mDigits[value].empty())
        return nullptr;
    //Return a pointer to a digit of the given value and remove it from the list
    else
    {
        ItemDigit* result = mDigits[value].back();
        mDigits[value].pop_back();
        return result;
    }
}