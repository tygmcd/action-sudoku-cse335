/**
 * @file ItemContainer.h
 * @author Connor Blackmer
 *
 * Class that acts as a container, derived from Item.
 */

#ifndef PROJECT1_GAMELIB_ITEMCONTAINER_H
#define PROJECT1_GAMELIB_ITEMCONTAINER_H

#include "Item.h"
#include "DeclarationContainer.h"
#include "ItemDigit.h"
#include "PlayingArea.h"

#include <random>

/**
 * Class which acts as a container.
 */
class ItemContainer : public Item {
private:
    ///Stores a vector of pointers to digits contained in the ItemContainer
    std::vector<std::shared_ptr<Item>> mContainedDigits;

	/// Declaration object for this specific type
	DeclarationContainer* mDeclaration = nullptr;

    /// Random number generator
    std::mt19937 mRandom;

    /// Previous X value (random)
    double mPreviousX = 0;

    /// Previous Y value (random)
    double mPreviousY = 0;

public:
    ItemContainer(Game *game,DeclarationContainer *dec,wxXmlNode& node);

    ///  Default constructor (disabled)
    ItemContainer() = delete;

    ///  Copy constructor (disabled)
    ItemContainer(const ItemContainer &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitContainer(this); }

    void Add(std::shared_ptr<Item> item);

    void MoveToPlayingArea(std::shared_ptr<PlayingArea> playingArea);

    /**
     * Get the random number generator
     * @return Pointer to the random number generator
     */
    std::mt19937 &GetRandom() {return mRandom;}

    bool IsValidLocation(double x, double y);
};

#endif //PROJECT1_GAMELIB_ITEMCONTAINER_H
