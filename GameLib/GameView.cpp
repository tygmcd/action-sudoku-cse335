/**
 * @file GameView.cpp
 * @author Tyler McDonald
 */

#include "pch.h"
#include "ids.h"
#include "GameView.h"
#include <wx/dcbuffer.h>

/// Animation frame duration in milliseconds
const int FrameDuration= 30;

/// Finish time delay (seconds)
const int DelayTime = 3;

/// Difference for key values
const int Difference = 48;

/// B key value
const int BKeyValue = 66;

/**
 * Initialize the GameView.
 * @param parent The parent window for this class
 */
void GameView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY,
           wxDefaultPosition, wxDefaultSize,
           wxFULL_REPAINT_ON_RESIZE);

    SetBackgroundStyle(wxBG_STYLE_PAINT);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel0, this, IDM_LEVEL0);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel1, this, IDM_LEVEL1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel2, this, IDM_LEVEL2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel3, this, IDM_LEVEL3);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnSolve, this, IDM_SOLVE);

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);
    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyPress, this);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);

    mStopWatch.Start();

}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent &event)
{
    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    if (!mGame.IsBoardFull())
    {
        mGame.GetScoreboard()->Update(elapsed);
    }
    mGame.GetPlayingArea()->Update(elapsed);
    mGame.GetSparty()->Update(elapsed);
    mGame.GetSparty()->UpdateHeadbutt(elapsed);
    mGame.GetSparty()->UpdateEating(elapsed);
    mGame.UpdateErrors(elapsed);
    if (mGame.IsBoardFull())
    {
        mFinishTime += elapsed;
        if (mFinishTime > DelayTime)
        {
            ResetStopwatch();
            mGame.IncrementLevel();
            mFinishTime = 0;
        }

    }

    // Create a graphics context
    auto gc =
        std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));


    // Tell the game class to draw
    wxRect rect = GetRect();
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight(), mTime);
}

/**
 * Handles timer event
 * @param event Timer event
 */
void GameView::OnTimer(wxTimerEvent &event)
{
    Refresh();
}

/**
 * Handle the left mouse button down event
 * @param event The mouse click event
 */
void GameView::OnLeftDown(wxMouseEvent &event)
{
    mGame.OnLeftDown(event.GetX(), event.GetY());
}

/**
 * Handle key press event
 * @param event The key press event
 */
void GameView::OnKeyPress(wxKeyEvent &event)
{
    if (event.GetKeyCode() == BKeyValue)
    {
        mGame.OnPressB();
    }
    if (event.GetKeyCode() == WXK_SPACE)
    {
        mGame.OnPressSpacebar();
    }
	if(event.GetKeyCode() >= '0' && event.GetKeyCode() <= '9') // checks the range of the keys that could be implemented
	{

		int number = event.GetKeyCode() - Difference; // subbing by this diff dives us the number that we want
		mGame.OnSpitKeys(number); // sends the number to the function to grab the number
	}
}


/**
 * Menu hander for Level>Level 0
 * @param event Mouse event
 */
void GameView::OnLevel0(wxCommandEvent& event)
{
    ResetStopwatch();

    mGame.SetLevelNumber(0);
    mGame.IncrementLevel();

}

/**
 * Menu hander for Level>Level 1
 * @param event Mouse event
 */
void GameView::OnLevel1(wxCommandEvent& event)
{
    ResetStopwatch();

    mGame.SetLevelNumber(1);
    mGame.IncrementLevel();
}

/**
 * Menu hander for Level>Level 2
 * @param event Mouse event
 */
void GameView::OnLevel2(wxCommandEvent& event)
{
    ResetStopwatch();

    mGame.SetLevelNumber(2);
    mGame.IncrementLevel();
}

/**
 * Menu hander for Level>Level 3
 * @param event Mouse event
 */
void GameView::OnLevel3(wxCommandEvent& event)
{
    ResetStopwatch();

    mGame.SetLevelNumber(3);
    mGame.IncrementLevel();
}

/**
 * Menu handler for File>Solve
 * @param event Mouse event
 */
void GameView::OnSolve(wxCommandEvent& event)
{
    mGame.Solve();
}

/**
 * Resets the stopwatch
 */
void GameView::ResetStopwatch()
{
    mStopWatch.Start(0);
    mTime = 0;
}