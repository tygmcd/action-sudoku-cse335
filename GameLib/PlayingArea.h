/**
 * @file PlayingArea.h
 * @author Tyler McDonald
 *
 * Contains declaration for PlayingArea class
 */

#ifndef PROJECT1_GAMELIB_PLAYINGAREA_H
#define PROJECT1_GAMELIB_PLAYINGAREA_H

#include <memory>
#include "Item.h"

/**
 * Class that represents the area on which the game is played on
 */
class PlayingArea {
private:
    ///Vector of shared pointers to the items
    std::vector<std::shared_ptr<Item>> mItems;

	/// 2D vector that represents the current values of all the numbers in the sudoku grid
	std::vector<std::vector<int>> mMasterList;

    void InitializeMasterList();

public:
    PlayingArea();

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void Add(std::shared_ptr<Item> item);

	std::shared_ptr<Item> HitTest(int x, int y);
    std::shared_ptr<Item> SpartyEatTest(int x, int y);
    std::shared_ptr<Item> SpartyHeadbuttTest(int x, int y);

    void Update(double elapsed);

    void Accept(ItemVisitor* visitor);

    void Clear();

    void Remove(std::shared_ptr<Item> item);

    /**
     * Get whether the specified cell of the sudoku board is filled
     * @param x The column to check
     * @param y The row to check
     * @return True if the cell is filled, False otherwise
     */
    bool GetCellFilled(int x, int y) { return mMasterList[x][y]!=-1; }

    /**
     * Get the value of the number in the specified cell of the sudoku board
     * @param x The column to check
     * @param y The row to check
     * @return The value of the number in the cell, -1 if the cell is empty
     */
    int GetCellValue(int x, int y) { return mMasterList[x][y]; }

    /**
     * Set the value of the digit of the specified cell on the sudoku board
     * @param x The column to set
     * @param y The row to set
     * @param value The value to set to. Set to -1 to indicate an empty cell
     */
    void SetCellValue(int x, int y, int value) { mMasterList[x][y] = value; }
};

#endif //PROJECT1_GAMELIB_PLAYINGAREA_H
