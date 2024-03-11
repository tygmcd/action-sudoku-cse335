/**
 * @file ItemXray.h
 * @author Connor Blackmer
 *
 * Class defining the ItemXray, derived from Item
 */

#ifndef PROJECT1_GAMELIB_ITEMXRAY_H
#define PROJECT1_GAMELIB_ITEMXRAY_H

#include <random>
#include "Item.h"
#include "ItemDigit.h"
#include "DeclarationXray.h"

/**
 * Class defining the ItemXray, derived from Item
 */
class ItemXray : public Item {
private:
    ///Stores a vector of pointers to digits contained in the ItemXray
    std::vector<std::shared_ptr<Item>> mContainedDigits;

    /// Pointer to declaration
    DeclarationXray* mDeclaration = nullptr;

    /// Random number generator
    std::mt19937 mRandom;


public:
    ItemXray(Game *game, DeclarationXray *dec, wxXmlNode& node);

    ///  Default constructor (disabled)
    ItemXray() = delete;

    ///  Copy constructor (disabled)
    ItemXray(const ItemXray &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Get the random number generator
     * @return Pointer to the random number generator
     */
    std::mt19937 &GetRandom() {return mRandom;}

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitXray(this); }

    void Add(std::shared_ptr<Item> item);

	std::shared_ptr<Item> Spit(int number);

    bool NumInListChecker(int targetNumber);
    /**
     * Gets the current size of the vector containing digits
     * @return Vector size
     */
    int GetCurrentSize() {return mContainedDigits.size();}

    /**
     * Gets the max capacity of the vector based on declaration xml
     * @return Vector full capacity
     */
    int GetXrayCapacity() {return mDeclaration->GetCapacity();}

    bool IsValidLocation(double x, double y);
};

#endif //PROJECT1_GAMELIB_ITEMXRAY_H
