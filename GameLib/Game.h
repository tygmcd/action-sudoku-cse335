/**
 * @file Game.h
 * @author Connor Blackmer
 *
 * Class that creates the game area, and holds the items we can manipulate.
 */

#ifndef PROJECT1_GAMELIB_GAME_H
#define PROJECT1_GAMELIB_GAME_H

#include "Item.h"
#include "Scoreboard.h"
#include "PlayingArea.h"
#include "Level.h"
#include "ItemSparty.h"
#include "ErrorPopup.h"
#include <memory>

/**
 * Class that creates the game area that holds the items we can manipulate.
 */
class Game {
private:
    /// Scoreboard associated with Game
    std::shared_ptr<Scoreboard> mScoreboard;

    /// Current level
    std::shared_ptr<Level> mLevel;

    /// Playing area for the game
    std::shared_ptr<PlayingArea> mPlayingArea;

    /// Sparty object for the game
    std::shared_ptr<ItemSparty> mSparty;

    /// List of popups currently on screen
    std::vector<std::shared_ptr<ErrorPopup>> mPopups;

    /// Scale for virtual pixels
    double mScale;

    /// X offset for virtual pixels
    double mXOffset;

    /// Y offset for virtual pixels
    double mYOffset;

    /// Offset mouse x-coordinate
    double mOX = 0;

    /// Offset mouse y-coordinate
    double mOY = 0;

    /// Positive offset mouse x-coordinate
    double mLastPositiveX = 0;

    /// Positive fffset mouse y-coordinate
    double mLastPositiveY = 0;

    ///The level number we are currently on
    int mLevelNumber = 0;

    /// True while game is showing instructions
    bool mStartingUp = true;

    ///Bool which is true if we won the level
    bool mLevelWon = false;


public:
    /**
     * Constructor
     */
    Game();

    /**
     * Destructor
    */
    virtual ~Game() = default;

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height, int time);

    /**
     * Gets scoreboard object associated with game
     * @return Scoreboard object
     */
    std::shared_ptr<Scoreboard> GetScoreboard() { return mScoreboard; }

    void OnLeftDown(int x, int y);
    void OnPressB();
    void HeadbuttItem();
    void OnPressSpacebar();
    void EatItem();
	void OnSpitKeys(int number);

    /**
     * Sets level within game
     * @param level level object
     */
    void SetLevel(std::shared_ptr<Level> level) { mLevel = level; };

    /**
     * Gets mOX
     * @return mOX
     */
    double GetOX() const { return mOX; }

    /**
    * Gets mOY
    * @return mOY
    */
    double GetOY() const { return mOY; }

    /**
     * Gets last positive x coord
     * @return x coord
     */
    double GetLastPositiveX() const { return mLastPositiveX; }

    /**
    * Gets last positive y coord
    * @return y coord
    */
    double GetLastPositiveY() const { return mLastPositiveY; }

    /**
    * Sets last positive x coord
    * @param x coord
    */
    void SetLastPositiveX(double x) {mLastPositiveX = x;}

    /**
    * Sets last positive y coord
    * @param y coord
    */
    void SetLastPositiveY(double y) {mLastPositiveY = y;}

    /**
     * Gets pointer to Sparty object
     * @return shared ptr to Sparty
     */
    std::shared_ptr<ItemSparty> GetSparty() { return mSparty; }

    /**
     * Gets pointer to PlayingArea
     * @return mPlayingArea
     */
    std::shared_ptr<PlayingArea> GetPlayingArea() { return mPlayingArea; }

    /**
     * Gets pointer to PlayingArea
     * @return mPlayingArea
     */
    std::shared_ptr<Level> GetLevel() { return mLevel; }

    /**
     * Resets mOX and mOY to 0
     */
    void ResetMouseCoordinates() { mOX = 0; mOY = 0; }

    void DrawInstructions(std::shared_ptr<wxGraphicsContext> graphics);
    void DrawEndCondition(std::shared_ptr<wxGraphicsContext> graphics);
    void AddError(std::string messsage);

    /**
     * Sets the number of the level we are in
     * @param num level to set to
     */
    void SetLevelNumber(int num){mLevelNumber = num;}

    /**
     * Resets the win or lose state of the level
     */
    void ResetLevelConditions(){mLevelWon = false;}

    /**
     * Sets Sparty pointer
     * @param sparty Pointer to Sparty
     */
    void SetSparty(std::shared_ptr<ItemSparty> sparty) { mSparty = sparty; }

    /**
     * Getter for mStartingUp (if the game is in Startup mode)
     * @return bool mStartingUp
     */
    bool GetStartingUp() { return mStartingUp; }

    /**
     * Sets mStartingUp
     * @param startingUp bool indicating if the game is in Startup mode
     */
    void SetStartingUp(bool startingUp) { mStartingUp = startingUp; }

    void UpdateErrors(double elapsed);

    void RemoveError();

    void ResetGameConditions();

    void Solve();

    void CheckSolution();

    bool IsBoardFull();

    void IncrementLevel();


};

#endif //PROJECT1_GAMELIB_GAME_H
