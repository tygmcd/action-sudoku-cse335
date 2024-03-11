/**
 * @file Level.h
 * @author Connor Blackmer
 *
 * Level Base class
 */

#ifndef PROJECT1_GAMELIB_LEVEL_H
#define PROJECT1_GAMELIB_LEVEL_H

#include <map>
#include "Declaration.h"

class Game;
class PlayingArea;

/**
 * Defines the level base class
 */
class Level {
private:
    ///Game which the level is in
    Game *mGame;

    ///Width of the level
    int mAreaWidth = 0;

    ///Height of the level
    int mAreaHeight = 0;

    ///Width of each tile within the level
    int mTileWidth = 0;

    ///Height of each tile within the level
    int mTileHeight = 0;

    ///Column position of the board in this level
    int mBoardColumn = 0;

    ///Row position of the board in this level
    int mBoardRow = 0;

    ///Solution to this level
    std::vector<int> mSolution;

    ///Declarations loaded by this level
    std::map<wxString, std::shared_ptr<Declaration>> mDeclarations;

public:
    ///Default constructor (disabled)
    Level() = delete;

    ///  Copy constructor (disabled)
    Level(const Level &) = delete;

    Level(Game *game);

    virtual ~Level();

    /**
     * Gets a pointer to the game we are in
     * @return Pointer to Game class
     */
    Game * GetGame(){return mGame;}

    void Load(const wxString &filename);

    /**
     * Gets the width of the level
     * @return Width of the level in virtual pixels
     */
    int GetWidth() {return mAreaWidth * mTileWidth;}

    /**
     * Gets the height of the level
     * @return Height of the level in virtual pixels
     */
    int GetHeight() {return mAreaHeight * mTileHeight;}

    /**
     * Gets the width of Tile
     * @return Width of Tile in virtual pixels
     */
    int GetTileWidth() {return mTileWidth; }

    /**
  * Gets the height of Tile
  * @return Height of Tile in virtual pixels
  */
    int GetTileHeight() {return mTileWidth; }

    /**
     * Gets the column in which the board starts
     * @return Column the board starts
     */
    int GetBoardColumn() {return mBoardColumn;}

    /**
     * Gets the row in which the board starts
     * @return Row the board starts
     */
    int GetBoardRow() {return mBoardRow;}

    /**
     * Gets a single digit of the solution
     * @param index Index of the solution to return
     * @return Digit of the solution in the specified index or -1 if it is out of range
     */
     int GetSolution(int index)
     {
         if (index >= 0 && index < mSolution.size())
            return mSolution[index];
         else
             return -1;
     }

     /**
      * Gets a declaration by ID
      * @param Id The ID of the declaration to get
      * @return Shared pointer to the declaration with the given ID or nullptr if it doesn't exist
      */
     std::shared_ptr<Declaration> GetDeclaration(const wxString Id)
     {
         if (mDeclarations.count(Id))
            return mDeclarations.at(Id);
         else
            return nullptr;
     }

     void Accept(DeclarationVisitor* visitor);

     int PositionXToCellColumn(int x);

     int PositionYToCellRow(int y);
};

#endif //PROJECT1_GAMELIB_LEVEL_H
