/**
 * @file GameView.h
 * @author Tyler McDonald
 *
 * Contains the declaration for our GameView class.
 */

#ifndef PROJECT1_GAMELIB_GAMEVIEW_H
#define PROJECT1_GAMELIB_GAMEVIEW_H

#include "Game.h"

/**
 * Class that represents the view/window of the Game.
 */
class GameView : public wxWindow {
private:
    /// Game object the GameView is associated with
    Game mGame;

    /// Timer for basic animation
    wxTimer mTimer;

    /// Time tracker for scoreboard purposes
    int mScoreboardTime = -2500;

    /// Animation time (stopwatch)
    int mTime = 0;

    /// Time for when sudoku finishes
    double mFinishTime = 0;

    /// Stopwatch for animations
    wxStopWatch mStopWatch;


    void OnPaint(wxPaintEvent& event);
    void OnTimer(wxTimerEvent& event);

public:
    void Initialize(wxFrame* parent);

    void OnLeftDown(wxMouseEvent &event);
    void OnKeyPress(wxKeyEvent &event);
    void OnLevel0(wxCommandEvent &event);
    void OnLevel1(wxCommandEvent &event);
    void OnLevel2(wxCommandEvent &event);
    void OnLevel3(wxCommandEvent &event);
    void OnSolve(wxCommandEvent & event);

    void ResetStopwatch();

    /**
     * Stop the timer so the window can close
     */
    void Stop() {mTimer.Stop();}

};

#endif //PROJECT1_GAMELIB_GAMEVIEW_H
