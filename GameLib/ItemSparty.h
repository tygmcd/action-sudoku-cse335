/**
 * @file ItemSparty.h
 * @author Joshua Mae
 *
 * Contains declaration for ItemSparty, derived from Item
 */

#ifndef PROJECT1_GAMELIB_ITEMSPARTY_H
#define PROJECT1_GAMELIB_ITEMSPARTY_H

#include "Item.h"
#include "DeclarationSparty.h"

/**
 * Class that represents the main component of the game, Sparty
 */
class ItemSparty : public Item {
private:
    /// True if Sparty is currently moving, false otherwise
    bool mIsMoving = false;

    /// Pointer to declaration
    DeclarationSparty* mDeclaration = nullptr;

    /// Set if Sparty is headbutting
    bool mIsHeadbutting = false;

    /// Tracks angle rotation
    double mHeadRotation = 0;

    /// Indicates whether or not to rotate Sparty in reverse
    bool mHeadReverse = false;

    /// Set if Sparty is eating
    bool mIsEating = false;

    /// Tracks angle rotation
    double mEatingRotation = 0;

    /// Indicates whether or not to rotate Sparty in reverse
    bool mEatingReverse = false;



public:
	ItemSparty(Game *game,DeclarationSparty *dec,wxXmlNode& node);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elapsed) override;

    /**
     * Getter to see if Sparty is currently moving
     * @return mIsMoving
     */
    bool GetIsMoving() { return mIsMoving; }
    void DrawMouth(std::shared_ptr<wxGraphicsContext> graphics);
    void DrawHead(std::shared_ptr<wxGraphicsContext> graphics);
    void MovementAnimation(double elapsed, double xOffset, double yOffset);

    /**
     * Getter for Sparty's Declaration
     * @return Pointer to DeclarationSparty
     */
    DeclarationSparty* GetDeclarationSparty() { return mDeclaration; }

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitSparty(this); }

    void UpdateHeadbutt(double elapsed);

    void UpdateEating(double elapsed);

    /**
     * Sets mIsHeadbutting bool
     * @param isHeadbutting true if Sparty is in headbutting mode
     */
    void SetIsHeadbutting(bool isHeadbutting) { mIsHeadbutting = true; }

    /**
    * Getter for mIsHeadbutting bool
    * @return mIsHeadbutting bool
    */
    bool GetIsHeadbutting() { return mIsHeadbutting; }

    /**
     * Getter for mHeadRotation
     * @return double mHeadRotation
     */
    double GetHeadRotation() { return mHeadRotation; }

    /**
    * Sets mIsEating bool
    * @param isEating true if Sparty is in eating mode
    */
    void SetIsEating(bool isEating) { mIsEating = true; }

    /**
    * Getter for mIsEating bool
    * @return mIsEating bool
    */
    bool GetIsEating() { return mIsEating; }

    /**
    * Getter for mEatingRotation
    * @return double mEatingRotation
    */
    double GetEatingRotation() { return mEatingRotation; }
};

#endif //PROJECT1_GAMELIB_ITEMSPARTY_H
