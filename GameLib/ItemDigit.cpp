/**
 * @file ItemDigit.cpp
 * @author Connor Blackmer
 */

#include "pch.h"
#include "ItemDigit.h"

/**
 * node implemented Item constructor
 * @param game pointer to the game the object is a part of
 * @param dec pointer to the declaration iof this specific object
 * @param node which will be how we will be loading in the item info from the level
 */
ItemDigit::ItemDigit(Game *game,DeclarationNumber *dec,wxXmlNode& node): ItemNumber(game,dec,node)
{
    mDeclaration = dec;
    XmlLoad(node);
}

/**
 * Draws digit on the playing area
 * @param graphics graphics context used
 */
void ItemDigit::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->DrawBitmap(*mDeclaration->GetBitmap(),GetX(),GetY(),mDeclaration->GetWidth(),mDeclaration->GetHeight());
}