/**
 * @file ErrorPopup.cpp
 * @author Connor Blackmer
 */

#include "pch.h"
#include "Game.h"
#include "ErrorPopup.h"

///Size of the font
const int FontSize = 30;

///Margins around the text
const int Margin = 20;

///Thickness of the border
const int LineThickness = 5;

/**
 * Error popup constructor
 * @param game pointer to the game the object is a part of
 * @param message Message to display on screen
 */

ErrorPopup::ErrorPopup(Game * game, std::string message)
{
    mGame = game;
    mMessage = message;
    mY = game->GetLevel()->GetHeight();
}

/**
 * Destructor
 */
ErrorPopup::~ErrorPopup()
{

}


/**
 * Draws an error messagee and moves it across the screen
 * @param graphics Graphics device to draw on
 */
void ErrorPopup::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    auto level = mGame->GetLevel();
    //
    //NOTE: Will probably have to move this to a class, since it needs to move and have mutliple
    //messages on the screen. Here for testing purposes.
    //
    int centerX = level->GetWidth() / 2;

    wxFont bigFont(wxSize(0, FontSize),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);

    double wid, hit;
    graphics->SetFont(bigFont, wxColour(255, 0, 0));
    graphics->GetTextExtent(mMessage, &wid, &hit);

    graphics->SetBrush(*wxWHITE_BRUSH);
    wxPen linePen(*wxBLACK, LineThickness);
    graphics->SetPen(linePen);

    double rectWidth = wid + Margin;
    double rectHeight = hit + Margin;

    graphics->DrawRectangle(centerX - rectWidth / 2, mY - rectHeight / 2,
                            rectWidth, rectHeight);

    graphics->DrawText(mMessage, (centerX - wid / 2), (mY - hit / 2));

}

/**
 * Updates the position of the popups on screen
 * @param elapsed time elapsed since last update
 */
void ErrorPopup::Update(double elapsed)
{
    mY = mY + (-mYSpeed * elapsed);
}

