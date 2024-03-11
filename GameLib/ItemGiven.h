/**
 * @file ItemGiven.h
 * @author Connor Blackmer
 *
 * Derived class of Item and Number, holds given digits.
 */

#ifndef PROJECT1_GAMELIB_ITEMGIVEN_H
#define PROJECT1_GAMELIB_ITEMGIVEN_H

#include "ItemNumber.h"
#include "DeclarationGiven.h"

/**
 * Derived class of Item and Number, holds given digits.
 */
class ItemGiven : public ItemNumber {
private:

    /// Pointer to declaration
    DeclarationNumber* mDeclaration = nullptr;
public:
    ItemGiven(Game *game,DeclarationNumber *dec,wxXmlNode& node);

    ///  Default constructor (disabled)
    ItemGiven() = delete;

    ///  Copy constructor (disabled)
    ItemGiven(const ItemGiven &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override
    {
        ItemNumber::Accept(visitor);
        visitor->VisitGiven(this);
    }
};

#endif //PROJECT1_GAMELIB_ITEMGIVEN_H
