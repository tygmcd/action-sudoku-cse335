/**
 * @file ItemSparty.cpp
 * @author Joshua Mae
 */

#include "pch.h"
#include "ItemSparty.h"
#include "Vector.h"
#include "Game.h"
#include "IsWallVisitor.h"

/// Character speed in pixels per second
const double MaxSpeed = 400.00;

/// The time for a headbutt cycle in seconds
const double HeadbuttTime = 0.5;

/// The time for an eating cycles in seconds
const double EatingTime = 0.5;



/**
 * node implemented Item constructor
 * @param game pointer to the game the object is a part of
 * @param dec pointer to the declaration iof this specific object
 * @param node which will be how we will be loading in the item info from the level
 */
ItemSparty::ItemSparty(Game *game,DeclarationSparty *dec,wxXmlNode& node): Item(game,dec,node)
{
    mDeclaration = dec;
    XmlLoad(node);
}

/**
 * Draws sparty on the playing area
 * @param graphics graphics context used
 */
void ItemSparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->DrawBitmap(*mDeclaration->GetBitmap(),0,0,mDeclaration->GetWidth(),mDeclaration->GetHeight());
    graphics->DrawBitmap(*mDeclaration->GetMouthBitmap(),0,0,
                         mDeclaration->GetMouthBitmap()->GetWidth(),mDeclaration->GetMouthBitmap()->GetHeight());

}

/**
 * Draws sparty mouth on the playing area
 * @param graphics graphics context used
 */
void ItemSparty::DrawMouth(std::shared_ptr<wxGraphicsContext> graphics)
{

    graphics->DrawBitmap(*mDeclaration->GetMouthBitmap(),0,0,
                         mDeclaration->GetMouthBitmap()->GetWidth(),mDeclaration->GetMouthBitmap()->GetHeight());

}

/**
 * Draws sparty head on the playing area
 * @param graphics graphics context used
 */
void ItemSparty::DrawHead(std::shared_ptr<wxGraphicsContext> graphics)
{
    // HARDCODED!! Needs to change when XML is loaded, images and values will come from declaration
    graphics->DrawBitmap(*mDeclaration->GetBitmap(),0,0,mDeclaration->GetWidth(),mDeclaration->GetHeight());
}

/**
 * Updates Sparty
 * @param elapsed Time since last Update
 */
void ItemSparty::Update(double elapsed)
{
    if (GetGame()->GetLastPositiveX() > 0 && GetGame()->GetLastPositiveY() > 0)
    {
        // Left side certain edge Sparty Movement
        if(GetGame()->GetLastPositiveX() - mDeclaration->GetTargetX() < 0)
        {
            // Left side bottom movement
            if (GetGame()->GetLastPositiveY() + mDeclaration->GetTargetY() > GetGame()->GetLevel()->GetHeight())
            {
                MovementAnimation(elapsed, GetGame()->GetLastPositiveX(),  GetGame()->GetLastPositiveY()-(GetGame()->GetLevel()->GetHeight() - mDeclaration->GetHeight()));
            }
            // Left side top movement
            else if (GetGame()->GetLastPositiveY() - mDeclaration->GetTargetY() < 0)
            {
                MovementAnimation(elapsed, GetGame()->GetLastPositiveX(), GetGame()->GetLastPositiveY() + mDeclaration->GetHeight()/2);
            }
            // General left side edge movement
            else
            {
                MovementAnimation(elapsed,GetGame()->GetLastPositiveX(),mDeclaration->GetHeight() - mDeclaration->GetTargetY());
            }
        }

        // Right side certain edge Sparty movement
        else if (GetGame()->GetLastPositiveX() + mDeclaration->GetTargetX()/2 > GetGame()->GetLevel()->GetWidth())
        {
            // Right side bottom movement
            if (GetGame()->GetLastPositiveY() + mDeclaration->GetTargetY() > GetGame()->GetLevel()->GetHeight())
            {
                MovementAnimation(elapsed, GetGame()->GetLastPositiveX()-(GetGame()->GetLevel()->GetWidth() - mDeclaration->GetWidth()), GetGame()->GetLastPositiveY()-(GetGame()->GetLevel()->GetHeight() - mDeclaration->GetHeight()));
            }
            // Right side top movement
            else if (GetGame()->GetLastPositiveY() - mDeclaration->GetTargetY() < 0)
            {
                MovementAnimation(elapsed, GetGame()->GetLastPositiveX()-(GetGame()->GetLevel()->GetWidth() - mDeclaration->GetWidth()), GetGame()->GetLastPositiveY() + mDeclaration->GetHeight()/2);
            }
            // Right side edge movement
            else
            {
                MovementAnimation(elapsed, GetGame()->GetLastPositiveX()-(GetGame()->GetLevel()->GetWidth() - mDeclaration->GetWidth()), mDeclaration->GetHeight() - mDeclaration->GetTargetY());
            }
        }

        // Top edge Sparty movement
        else if (GetGame()->GetLastPositiveY() - mDeclaration->GetTargetY() < 0)
        {
            MovementAnimation(elapsed, mDeclaration->GetTargetX(), GetGame()->GetLastPositiveY() + mDeclaration->GetHeight()/2);
        }

        // Bottom edge Sparty movement
        else if (GetGame()->GetLastPositiveY() + mDeclaration->GetTargetY() > GetGame()->GetLevel()->GetHeight())
        {
            MovementAnimation(elapsed, mDeclaration->GetTargetX(), GetGame()->GetLastPositiveY()-(GetGame()->GetLevel()->GetHeight() - mDeclaration->GetHeight()));
        }

        // Movement anywhere else besides the edges
        else
        {
            MovementAnimation(elapsed,mDeclaration->GetTargetX(), mDeclaration->GetHeight() - mDeclaration->GetTargetY());
        }
    }
}

/**
 * Does the vector math for the animation
 * @param elapsed Time since last Update
 * @param xOffset y - coord offset
 * @param yOffset x - coord offset
 */
void ItemSparty::MovementAnimation(double elapsed, double xOffset, double yOffset)
{
    mIsMoving = true;
    Vector finalPosition = Vector(GetGame()->GetLastPositiveX() - xOffset, GetGame()->GetLastPositiveY() - yOffset);
    Vector currentPosition = Vector(this->GetX(), this->GetY());
    Vector distanceToFinal = finalPosition - currentPosition;
    Vector direction = *(distanceToFinal.Normalize());

    Vector delta = Vector(direction.X() * elapsed * MaxSpeed, direction.Y() * elapsed * MaxSpeed);

    //Checks if Sparty is in a wall
    IsWallVisitor visitor;
    auto area = GetGame()->GetPlayingArea();
    auto item = area->HitTest(GetX() + delta.X(), GetY() + delta.Y());
    if(item.get() != this && item){
        item->Accept(&visitor);
    }

    if(visitor.IsWall())
    {
        this->SetLocation(currentPosition.X(), currentPosition.Y());
        GetGame()->SetLastPositiveX(GetX() + xOffset);
        GetGame()->SetLastPositiveY(GetY() + yOffset);
        GetGame()->ResetMouseCoordinates();
        mIsMoving = false;
    }
    else if((delta.Length() >= distanceToFinal.Length()) ||
        (finalPosition.X() == currentPosition.X() && finalPosition.Y() == currentPosition.Y()))
    {
        this->SetLocation(finalPosition.X(), finalPosition.Y());
        GetGame()->ResetMouseCoordinates();
        mIsMoving = false;
    }
    else
    {
        this->SetLocation(currentPosition.X() + delta.X(),
                          currentPosition.Y() + delta.Y());
    }
}

/**
 * Updates Sparty's headbutt animation
 * @param elapsed time elapsed since last call
 */
void ItemSparty::UpdateHeadbutt(double elapsed)
{

    if (mHeadRotation >= this->GetDeclarationSparty()->GetHeadPivotAngle())
    {
        mHeadReverse = true;
        GetGame()->HeadbuttItem();
    }

    if (mIsHeadbutting && !mHeadReverse &&  mHeadRotation < this->GetDeclarationSparty()->GetHeadPivotAngle())
    {
        mHeadRotation += elapsed / (HeadbuttTime / 2);
    }
    else if (mIsHeadbutting && mHeadReverse && mHeadRotation > 0)
    {
        mHeadRotation -= elapsed/ (HeadbuttTime / 2);
    }
    else
    {
        mHeadRotation = 0;
        mHeadReverse = false;
        mIsHeadbutting = false;
    }
}

/**
 * Updates Sparty's eating animation
 * @param elapsed time elapsed since last call
 */
void ItemSparty::UpdateEating(double elapsed)
{

    if (mEatingRotation >= this->GetDeclarationSparty()->GetMouthPivotAngle())
    {
        mEatingReverse = true;
        GetGame()->EatItem();
    }

    if (mIsEating && !mEatingReverse &&  mEatingRotation < this->GetDeclarationSparty()->GetMouthPivotAngle())
    {
        mEatingRotation += elapsed / (EatingTime  / 2);
    }
    else if (mIsEating && mEatingReverse && mEatingRotation > 0)
    {
        mEatingRotation -= elapsed / (EatingTime  / 2);
    }
    else
    {
        mEatingRotation = 0;
        mEatingReverse = false;
        mIsEating = false;
    }
}