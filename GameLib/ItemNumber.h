/**
 * @file ItemNumber.h
 * @author Connor Blackmer
 *
 * Derived class of Item, base class for all digits
 */

#ifndef PROJECT1_GAMELIB_ITEMNUMBER_H
#define PROJECT1_GAMELIB_ITEMNUMBER_H

#include "Item.h"
#include "DeclarationNumber.h"

/**
 * Derived class of Item, base class for all digits
 */
class ItemNumber : public Item {
private:
    /// Pointer to DeclarationNumber
    DeclarationNumber* mNumberDeclaration = nullptr;

    /// Whether this digit is currently in the sudoku grid
    bool mInSudokuGrid = false;

public:
    ItemNumber(Game *game,DeclarationNumber *dec,wxXmlNode& node);

    ///  Default constructor (disabled)
    ItemNumber() = delete;

    ///  Copy constructor (disabled)
    ItemNumber(const ItemNumber &) = delete;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitNumber(this); }

    int GetValue();

    /**
     * Getter for DeclarationNumber
     * @return Pointer to DeclarationNumber
     */
    DeclarationNumber* GetNumberDeclaration() { return mNumberDeclaration; }

    /**
     * Gets whether this digit is currently in the sudoku grid
     * @return Whether this item is currently in the sudoku grid
     */
    bool GetInSudokuGrid() { return mInSudokuGrid; }

    /**
     * Sets whether this item is currently in the sudoku grid
     * @param value The value to set
     */
    void SetInSudokuGrid(bool value) { mInSudokuGrid = value; }

    void SetLocation(double x, double y) override;
};

#endif //PROJECT1_GAMELIB_ITEMNUMBER_H
