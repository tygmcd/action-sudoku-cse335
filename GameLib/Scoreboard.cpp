/**
 * @file Scoreboard.cpp
 * @author Tyler McDonald
 */

#include "pch.h"
#include "Scoreboard.h"
#include <sstream>
#include <iomanip>

using namespace std;

/// Num of seconds in a minute
const int NumSeconds = 60;

/// Restarts scoreboard at -2.5 seconds to delay its drawing
const double RestartTime = -2.5;

/// Font size
const int FontSize = 64;

/// Scoreboard position
const int ScoreboardCoordinate = 20;

/// Fill width for zeroes
const int ZeroPadding = 2;

/**
 * Draw the Scoreboard
 * @param graphics graphics context used
 */
void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Creates a 20-pixel tall font
    wxFont font(wxSize(0, FontSize),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    graphics->SetFont(font, wxColour(*wxWHITE));


    mSecondsStream << mSeconds / NumSeconds << ":";
    mSecondsStream << std::setw(ZeroPadding) << std::setfill('0') << mSeconds % NumSeconds;

    graphics->DrawText(wxString(mSecondsStream.str()),  // Text to draw
                ScoreboardCoordinate,     // x coordinate for the left size of the text
                ScoreboardCoordinate);    // y coordinate for the top of the text

    mSecondsStream.str("");

}

/**
 * Increment seconds following every timer fire
 */
void Scoreboard::IncrementSeconds()
{
    mSeconds++;
}

/**
 * Resets scorebaord time
 */
void Scoreboard::ResetScoreboard()
{
    mUpdateTime = RestartTime;
    mSeconds = 0;
    mSecondsStream.str("");
}

/**
 * Updates the Scoreboard
 * @param elapsed time since last update
 */
void Scoreboard::Update(double elapsed)
{
    if (mUpdateTime > 1)
    {
        IncrementSeconds();
        mUpdateTime = 0;
    }

    mUpdateTime += elapsed;

}