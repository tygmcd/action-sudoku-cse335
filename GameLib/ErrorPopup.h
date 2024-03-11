/**
 * @file ErrorPopup.h
 * @author Connor Blackmer
 */

#ifndef ACTIONSUDOKU_GAMELIB_ERRORPOPUP_H
#define ACTIONSUDOKU_GAMELIB_ERRORPOPUP_H

class Game;

/**
 * Creates and manages an error popup on the screen
 */
class ErrorPopup {
private:
    /// Game the errors are contained in
    Game* mGame;
    ///Message which displays on the popup
    std::string mMessage;

    ///Speed the popups move across the screen
    int mYSpeed = 300;

    ///Y axis location of the popup
    int mY = 0;
public:

    ErrorPopup(Game * game, std::string message);

    ///Default constructor (disabled)
    ErrorPopup() = delete;

    ///  Copy constructor (disabled)
    ErrorPopup(const ErrorPopup &) = delete;

    /// Destructor
    ~ErrorPopup();

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    void Update(double elapsed);

    /**
     * Gets the Y location of the popup
     * @return Y location of the popup
     */
    int GetYLocation(){return mY;}
};

#endif //ACTIONSUDOKU_GAMELIB_ERRORPOPUP_H
