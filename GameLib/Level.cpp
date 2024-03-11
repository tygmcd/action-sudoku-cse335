/**
 * @file Level.cpp
 * @author Connor Blackmer
 */

#include "pch.h"
#include "Game.h"
#include "PlayingArea.h"
#include "Level.h"
#include "DeclarationDigit.h"
#include "DeclarationGiven.h"
#include "DeclarationBackground.h"
#include "DeclarationContainer.h"
#include "DeclarationSparty.h"
#include "DeclarationXray.h"
#include "DeclarationWall.h"

#include "Item.h"
#include "ItemDigit.h"
#include "ItemGiven.h"
#include "ItemBackground.h"
#include "ItemContainer.h"
#include "ItemSparty.h"
#include "ItemXray.h"
#include "ItemWall.h"

#include "GetSpartyVisitor.h"
#include "FindItemContainerVisitor.h"

/// The number of rows/columns in the sudoku board
const int BoardSize = 9;

/**
 * Constructor
 * @param game game to load the level into
 */
Level::Level(Game *game) : mGame(game)
{

}

/**
* Destructor
*/
Level::~Level()
{

}

/**
* Load a level from XML
 * @param filename The filename of the XML file to load the level from
*/
void Level::Load(const wxString &filename)
{
    //Load the XML document
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Level file");
        return;
    }

    //Clear the level here
    mDeclarations.clear();
    mSolution.clear();

    //Get the XML document root node
    auto root = xmlDoc.GetRoot();

    //Get the game values from the root node
    root->GetAttribute(L"width", L"1").ToInt(&mAreaWidth);
    root->GetAttribute(L"height", L"1").ToInt(&mAreaHeight);
    root->GetAttribute(L"tilewidth", L"1").ToInt(&mTileWidth);
    root->GetAttribute(L"tileheight", L"1").ToInt(&mTileHeight);

    // Traverse the children of the root node
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        //Check what type of node this is
        auto name = child->GetName();
        if (name == L"game")
        {
            //Get the position of the board
            child->GetAttribute(L"col", L"0").ToInt(&mBoardColumn);
            child->GetAttribute(L"row", L"0").ToInt(&mBoardRow);

            //Get the solution
            wxString solutionString = child->GetNodeContent();
            for ( wxString::const_iterator it = solutionString.begin(); it != solutionString.end(); ++it )
            {
                char solutionCharacter = *it;
                if (solutionCharacter != ' ')
                    mSolution.push_back(solutionCharacter - '0');
            }
        }
        else if (name == L"declarations")
        {
            //Iterate over the child nodes
            auto declaration = child->GetChildren();
            for( ; declaration; declaration=declaration->GetNext())
            {
                //Construct the declarations
                auto declarationName = declaration->GetName();
                wxString declarationId = declaration->GetAttribute(L"id", L"INVALID");
                if (declarationName=="digit")
                {
                    mDeclarations[declarationId] = std::make_shared<DeclarationDigit>(this, *declaration);
                }
                else if (declarationName=="given")
                {
                    mDeclarations[declarationId] = std::make_shared<DeclarationGiven>(this, *declaration);
                }
                else if (declarationName=="background")
                {
                    mDeclarations[declarationId] = std::make_shared<DeclarationBackground>(this, *declaration);
                }
                else if (declarationName=="xray")
                {
                    mDeclarations[declarationId] = std::make_shared<DeclarationXray>(this, *declaration);
                }
                else if (declarationName=="sparty")
                {
                    mDeclarations[declarationId] = std::make_shared<DeclarationSparty>(this, *declaration);
                }
                else if (declarationName=="container")
                {
                    mDeclarations[declarationId] = std::make_shared<DeclarationContainer>(this, *declaration);
                }
                else if (declarationName=="wall")
                {
                    mDeclarations[declarationId] = std::make_shared<DeclarationWall>(this, *declaration);
                }
            }
        }
        else if (name == L"items")
        {
            //Iterate over the child nodes
            auto item = child->GetChildren();
            for( ; item; item=item->GetNext())
            {
                //Construct the declarations, test
                auto itemName = item->GetName();
                wxString itemId = item->GetAttribute(L"id", L"INVALID");

                if (itemName=="sparty")
                {
                    mDeclarations[itemId]->Create(*item);
                }
                else if (itemName=="container")
                {
					mGame->GetPlayingArea()->Add(mDeclarations[itemId]->Create(*item));
                    auto content = item->GetChildren();
                    for( ; content; content=content->GetNext())
                    {
                        wxString contentId = content->GetAttribute(L"id", L"INVALID");
                        FindItemContainerVisitor visitor(itemId);
                        GetGame()->GetPlayingArea()->Accept(&visitor);
                        visitor.GetItemContainer()->Add(mDeclarations[contentId]->Create(*content));
                    }
                }
				else
				{
					mGame->GetPlayingArea()->Add(mDeclarations[itemId]->Create(*item));
				}
            }
        }
    }
}

/**
 * Accept a visitor for the collection of declarations
 * @param visitor The visitor for the collection
 */
void Level::Accept(DeclarationVisitor* visitor)
{
    for (const auto& declaration : mDeclarations)
    {
        declaration.second->Accept(visitor);
    }
}

/**
 * Convert an x position in virtual pixels to a column in the sudoku board
 * @param x The position to convert
 * @return The column in the sudoku board, or -1 if out of bounds
 */
int Level::PositionXToCellColumn(int x)
{
    int cellX = (int)floor((x - (mBoardColumn*mTileWidth))/mTileWidth);

    if (cellX < 0 || cellX>=BoardSize)
        return -1;

    return cellX;
}

/**
 * Convert a y position in virtual pixels to a row in the sudoku board
 * @param y The position to convert
 * @return The row in the sudoku board, or -1 if out of bounds
 */
int Level::PositionYToCellRow(int y)
{
    int cellY = (int)floor((y - (mBoardRow*mTileHeight))/mTileHeight);

    if (cellY < 0 || cellY>=BoardSize)
        return -1;

    return cellY;
}