/**
 * @file ItemWall.cpp
 * @author Connor Blackmer
 */

#include "pch.h"
#include "DeclarationWall.h"
#include "ItemWall.h"

/**
 * node implemented Item constructor
 * @param game pointer to the game the object is a part of
 * @param dec pointer to the declaration iof this specific object
 * @param node which will be how we will be loading in the item info from the level
 */
ItemWall::ItemWall(Game *game, DeclarationWall *dec, wxXmlNode& node) : Item(game, dec, node)
{
    mDeclaration = dec;
    XmlLoad(node);
}

/**
 * Draws Wall on the playing area
 * @param graphics graphics context used
 */
void ItemWall::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->DrawBitmap(*mDeclaration->GetBitmap(),GetX(),GetY(),mDeclaration->GetWidth(),mDeclaration->GetHeight());
}