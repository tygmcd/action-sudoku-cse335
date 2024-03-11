/**
 * @file Game.cpp
 * @author Connor Blackmer
 */

#include "pch.h"
#include "Game.h"
#include "Item.h"
#include "ItemBackground.h"
#include "ItemDigit.h"
#include "ItemSparty.h"
#include "ItemGiven.h"
#include "GetSpartyVisitor.h"
#include "FindItemContainerVisitor.h"
#include "ItemDigitVisitor.h"
#include "GetAllDigitsVisitor.h"
#include "GameView.h"

/// Start with level 1
const wxString Level1Filename = "levels/level1.xml";

///Message that displays when the level is finished and correct
const wxString LevelCompleteCorrect = "Level Complete!";

///Message that displays when the level is finished and incorrect
const wxString LevelCompleteIncorrect = "Incorrect!";

///The number rows/columns in the sudoku board
const int BoardSize = 9;

///The X offset from Sparty's position to regurgitate digits at
const int SpartyRegurgitationXOffset = 60;

///The Y offset from Sparty's position to regurgitate digits at
const int SpartyRegurgitationYOffset = 40;

///How long the startup instructions should display for in milliseconds
const int StartupDelay = 3000;

///The width of the instructions background rectangle
const int InstructionRectWidth = 600;

///The height of the instructions background rectangle
const int InstructionRectHeight = 300;

///The font size of the main instructions text
const int InstructionsFontSize = 80;

///The font size of the smaller instructions text
const int InstructionsSmallFontSize = 60;

///The font size of the level completion text
const int CompletionTextFontSize = 100;

/**
 * Constructor
 */
Game::Game()
{
    mScoreboard = std::make_shared<Scoreboard>();
    mLevel = std::make_shared<Level>(this);
    mPlayingArea = std::make_shared<PlayingArea>();

    this->SetLevelNumber(1);
    mLevel->Load(Level1Filename);
}

/**
 * Draw the game
 * @param graphics Graphics device to draw on
 * @param width Width of the window
 * @param height Height of the window
 * @param time Time elapsed throughout application runtime
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height, int time)
{
    // Determine the size of the playing area in pixels
    // This is up to you...
    int pixelWidth = mLevel->GetWidth();
    int pixelHeight = mLevel->GetHeight();

    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    // Draw playing area
    mPlayingArea->Draw(graphics);

    // --------- New state, draw Sparty here --------------
    graphics->PushState();
    graphics->Translate(mSparty->GetX(), mSparty->GetY());

    // Check if in headbutting mode, rotate bitmap if so
    // If not, draw Sparty normally
    if (mSparty->GetIsHeadbutting())
    {
        graphics->Translate(mSparty->GetDeclarationSparty()->GetHeadPivotX(),
                            mSparty->GetDeclarationSparty()->GetHeadPivotY());
        graphics->Rotate(mSparty->GetHeadRotation());
        graphics->Translate(-mSparty->GetDeclarationSparty()->GetHeadPivotX(),
                            -mSparty->GetDeclarationSparty()->GetHeadPivotY());
        mSparty->Draw(graphics);
    }
    else if (mSparty->GetIsEating() && mSparty->GetDeclarationSparty()->GetFront() == 1)
    {

        graphics->PushState();
        graphics->Translate(mSparty->GetDeclarationSparty()->GetMouthPivotX(),
                            mSparty->GetDeclarationSparty()->GetMouthPivotY());
        graphics->Rotate(mSparty->GetEatingRotation());
        graphics->Translate(-mSparty->GetDeclarationSparty()->GetMouthPivotX(),
                            -mSparty->GetDeclarationSparty()->GetMouthPivotY());
        mSparty->DrawMouth(graphics);
        graphics->PopState();

        mSparty->DrawHead(graphics);

    }
    else if (mSparty->GetIsEating() && mSparty->GetDeclarationSparty()->GetFront() == 2)
    {
        mSparty->DrawHead(graphics);
        graphics->Translate(mSparty->GetDeclarationSparty()->GetMouthPivotX(),
                            mSparty->GetDeclarationSparty()->GetMouthPivotY());
        graphics->Rotate(mSparty->GetEatingRotation());
        graphics->Translate(-mSparty->GetDeclarationSparty()->GetMouthPivotX(),
                            -mSparty->GetDeclarationSparty()->GetMouthPivotY());
        mSparty->DrawMouth(graphics);
    }
    else
    {
        mSparty->Draw(graphics);
    }
    graphics->PopState();
    // --------------  End of state ----------------

    // Draw scoreboard
    if (time > StartupDelay)
    {
        mStartingUp = false;
        mScoreboard->Draw(graphics);
    }

    if(time <= StartupDelay && !mLevelWon)
    {
        DrawInstructions(graphics);
    }

    // Check solution, draw end condition if level is complete
    if (IsBoardFull())
    {
        CheckSolution();
        DrawEndCondition(graphics);
    }

    for(auto popup: mPopups)
    {
        popup->Draw(graphics);
    }

    RemoveError();
    graphics->PopState();

}

/**
* Handle a mouse click
* @param x X location clicked on
* @param y Y location clicked on
*/
void Game::OnLeftDown(int x, int y)
{
    if (!mStartingUp)
    {
        mOX = (x - mXOffset) / mScale;
        mOY = (y - mYOffset) / mScale;

        if ((mOX >= 0 && mOX <= mLevel->GetWidth()) && (mOY >= 0 && mOY <=  mLevel->GetHeight()))
        {
            mLastPositiveX = mOX;
            mLastPositiveY = mOY;
        }
    }

}

/**
 * Headbutts an Item
 */
void Game::HeadbuttItem()
{
    std::shared_ptr<Item> item = mPlayingArea->SpartyHeadbuttTest(mSparty->GetX(), mSparty->GetY());
    if (item != nullptr)
    {
        FindItemContainerVisitor visitor(item->GetID());
        mPlayingArea->Accept(&visitor);
        if (visitor.GetItemContainer() != nullptr)
        {
            visitor.GetItemContainer()->MoveToPlayingArea(mPlayingArea);

        }
    }

}


/**
* Handle a b key press event
*/
void Game::OnPressB()
{
    if(!mSparty->GetIsMoving() && !mStartingUp)
    {
        mSparty->SetIsHeadbutting(true);
    }
}

/**
 * Eats an Item on the game screen
 */
void Game::EatItem()
{
    std::shared_ptr<Item> item = mPlayingArea->SpartyEatTest(mSparty->GetX(), mSparty->GetY());
    if (item != nullptr)
    {
        FindItemContainerVisitor visitor;
        mPlayingArea->Accept(&visitor);

        ItemDigitVisitor digitVisitor;
        item->Accept(&digitVisitor);

        if (digitVisitor.GetEatable())
        {
            if((visitor.GetItemXray()->GetCurrentSize() < visitor.GetItemXray()->GetXrayCapacity()))
            {
                mPlayingArea->Remove(item);
                visitor.GetItemXray()->Add(item);
            }
            else
            {
                AddError("I'm Full!");
            }
        }
    }

}

/**
* Handle a spacebar press event
*/
void Game::OnPressSpacebar()
{
    if (!mSparty->GetIsMoving() && !mStartingUp)
    {
        mSparty->SetIsEating(true);
    }

}


/**
* this function will take care of the events of fetching and drawing the spitted number out of the xray container
 * @param number which will be the number that we will be looking for in the xray container
*/
void Game::OnSpitKeys(int number)
{
	// retrieving the numbers from the xray.
	FindItemContainerVisitor visitor; // goes to the visitor to grab the  specific number
	mPlayingArea->Accept(&visitor);

    // Getting width and height calculations
    double tileWidth = (mLastPositiveX / GetLevel()->GetTileWidth());
    double TileHeight = (mLastPositiveY / GetLevel()->GetTileHeight());


	if(GetLevel()->PositionXToCellColumn(mLastPositiveX) != -1 && GetLevel()->PositionYToCellRow(mLastPositiveY) != -1) // if we are spitting out in the grid
	{
		// Now we will be checking if the column is unoccupied(-1), if it is, we will be occupying it(spat digit)

		if(!mPlayingArea->GetCellFilled(GetLevel()->PositionXToCellColumn(mLastPositiveX),
										GetLevel()->PositionYToCellRow(mLastPositiveY)))
		{
			std::shared_ptr<Item> digit = visitor.GetItemXray()->Spit(number); // sends that number to get checked

			if(digit != nullptr)
			{
				digit->SetLocation(floor(GetLevel()->GetTileWidth() * floor(tileWidth)),
								   floor(GetLevel()->GetTileHeight() * floor(TileHeight)));
				mPlayingArea->Add(digit);
			}
		}
		else
		{
            if (visitor.GetItemXray()->NumInListChecker(number))
			AddError("Something is already there!");
		}

	}
	else // if the spot to spit out is not in the grid
	{
		if(visitor.GetItemXray()->NumInListChecker(number))
		{
			std::shared_ptr<Item> digit = visitor.GetItemXray()->Spit(number); // sends that number to get checked
			digit->SetLocation(mSparty->GetX()+SpartyRegurgitationXOffset,mSparty->GetY()+SpartyRegurgitationYOffset);
			mPlayingArea->Add(digit);
		}

	}

}

/**
 * Draws the instructions when the game begins
 * @param graphics Graphics device to draw on
 */
void Game::DrawInstructions(std::shared_ptr<wxGraphicsContext> graphics)
{
    //
    // Draws the rectangle
    //
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->SetPen(*wxBLACK_PEN);
    int centerX = mLevel->GetWidth() / 2;
    int centerY = mLevel->GetHeight() / 2;
    int rectWidth = InstructionRectWidth;
    int rectHeight = InstructionRectHeight;
    graphics->DrawRectangle(centerX - rectWidth / 2, centerY - rectHeight / 2,
                            rectWidth, rectHeight);

    //
    // Draw some text
    //
    wxFont bigFont(wxSize(0, InstructionsFontSize),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);

    graphics->SetFont(bigFont, wxColour(0, 128, 0));
    double wid, hit;
    graphics->GetTextExtent(L"Level 0 Begin", &wid, &hit);

    //NOTE: This might need to be changed to a stringstream later
    graphics->DrawText(L"Level " + std::to_string(mLevelNumber) + " Begin", (centerX - wid / 2), (centerY - hit / 2) - 100);
    //
    // Draw some text
    //
    int smallSize = InstructionsSmallFontSize;
    wxFont smallFont(wxSize(0, smallSize),
                     wxFONTFAMILY_SWISS,
                     wxFONTSTYLE_NORMAL,
                     wxFONTWEIGHT_BOLD);

    graphics->SetFont(smallFont, wxColour(0, 0, 0));
    graphics->GetTextExtent(L"space: Eat", &wid, &hit);
    graphics->DrawText(L"space: Eat", (centerX - wid / 2), (centerY - hit / 2));
    graphics->GetTextExtent(L"0-8: Regurgitate", &wid, &hit);
    graphics->DrawText(L"0-8: Regurgitate", (centerX - wid / 2), (centerY - hit / 2) + (smallSize));
    graphics->GetTextExtent(L"B: Headbutt", &wid, &hit);
    graphics->DrawText(L"B: Headbutt", (centerX - wid / 2), (centerY - hit / 2) + (smallSize * 2));
}

/**
 * Draws a failure or success depending on the end state
 * @param graphics Graphics device to draw on
 */
void Game::DrawEndCondition(std::shared_ptr<wxGraphicsContext> graphics)
{

    int centerX = mLevel->GetWidth() / 2;
    int centerY = mLevel->GetHeight() / 2;
    //
    // Draw some text
    //
    wxFont bigFont(wxSize(0, CompletionTextFontSize),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);

    graphics->SetFont(bigFont, wxColour(0, 128, 0));

    double wid, hit;
    if(mLevelWon)
    {
        graphics->GetTextExtent(LevelCompleteCorrect, &wid, &hit);
        graphics->DrawText(LevelCompleteCorrect, (centerX - wid / 2), (centerY - hit / 2));
    }
    else
    {
        graphics->GetTextExtent(LevelCompleteIncorrect, &wid, &hit);
        graphics->DrawText(LevelCompleteIncorrect, (centerX - wid / 2), (centerY - hit / 2));
    }
}


/**
 * Resets certain game conditions to defaults (changing levels)
 */
void Game::ResetGameConditions()
{
    ResetMouseCoordinates();
    mLastPositiveX = 0;
    mLastPositiveY = 0;
}

/**
* Push an error to the game screen
 * @param message Any given message to show an error
*/
void Game::AddError(std::string message)
{
    auto popup = std::make_shared<ErrorPopup>(this, message);
    mPopups.push_back(popup);
}

/**
 * Updates the position of the errors
 * @param elapsed time since the last update
 */
void Game::UpdateErrors(double elapsed)
{
    for(auto popup: mPopups)
    {
        popup->Update(elapsed);
    }
}

/**
 * Removes the top most error if it's out of bounds
 */
void Game::RemoveError()
{
    if(!mPopups.empty())
    {
        auto popup = mPopups[0];
        if(popup->GetYLocation() < 0){
            mPopups.erase(begin(mPopups));
        }
    }
}

/**
 * Attempt to solve the sudoku puzzle
 */
void Game::Solve()
{
    //Get all the free digits
    std::shared_ptr<GetAllDigitsVisitor> visitor = std::make_shared<GetAllDigitsVisitor>();
    mPlayingArea->Accept(visitor.get());

    //Iterate over the sudoku grid
    for (int y=0; y<BoardSize; y++)
    {
        for (int x=0; x<BoardSize; x++)
        {
            //Get the coordinates of the cell
            int cellX = (mLevel->GetBoardColumn() + x)*mLevel->GetTileWidth();
            int cellY = (mLevel->GetBoardRow() + y)*mLevel->GetTileHeight();

            //If the cell is already filled, skip it
            if (mPlayingArea->GetCellFilled(x, y))
                continue;

            //Get the solution value for this cell
            int solutionValue = mLevel->GetSolution((y*BoardSize) + x);

            //Get a digit from the visitor with the correct value
            ItemDigit* solutionDigit = visitor->PopDigitOfValue(solutionValue);

            //Check whether the digit popped is null. If so, skip to the next cell
            if (solutionDigit == nullptr)
                continue;

            //Teleport the digit to the correct position
            solutionDigit->SetLocation(cellX, cellY);
        }
    }

    //Check the solution
    CheckSolution();
}

/**
* Check the solution
*/
void Game::CheckSolution()
{
    bool solutionValid = true;

    //Iterate over the sudoku board
    for (int x=0; x<BoardSize; x++)
    {
        for (int y=0; y<BoardSize; y++)
        {
            //Get the correct value for this cell
            int correctValue = mLevel->GetSolution(x + y*BoardSize);

            //Get the actual value for this cell
            int actualValue = mPlayingArea->GetCellValue(x, y);

            //If they don't match, the solution is invalid
            if (correctValue != actualValue)
            {
                solutionValid = false;
                break;
            }
        }
    }

    //Display whether the solution was correct
    if (solutionValid)
    {
        mLevelWon = true;
    }



}

/**
 * Checks to see if the playing area board is full or not
 * @return true if full
 */
bool Game::IsBoardFull()
{
    for (int x=0; x<BoardSize; x++)
    {
        for (int y=0; y<BoardSize; y++)
        {
            if (mPlayingArea->GetCellValue(x, y) == -1)
            {
                return false;
            }
        }
    }

    return true;
}

/**
 * Goes to the next level after solving current
 */
void Game::IncrementLevel()
{
    if (mLevelWon)
    {
        if (mLevelNumber != 3)
        {
            mLevelNumber++;
        }
    }

    GetPlayingArea()->Clear();
    if (mLevelNumber == 1)
    {
        GetLevel()->Load("levels/level1.xml");
    }
    else if (mLevelNumber == 2)
    {
        GetLevel()->Load("levels/level2.xml");
    }
    else if (mLevelNumber == 3)
    {
        GetLevel()->Load("levels/level3.xml");
    }
    else
    {
        GetLevel()->Load("levels/level0.xml");
    }

    GetScoreboard()->ResetScoreboard();

    SetStartingUp(true);
    ResetGameConditions();
    ResetLevelConditions();
}
