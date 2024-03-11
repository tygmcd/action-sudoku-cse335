/**
 * @file ItemDigit.h
 * @author Connor Blackmer
 *
 * Derived class of Item and Number, holds a mutable digit.
 */

#ifndef PROJECT1_GAMELIB_ITEMDIGIT_H
#define PROJECT1_GAMELIB_ITEMDIGIT_H

#include "ItemNumber.h"
#include "DeclarationDigit.h"

/**
 * Derived class of Item and Number, holds a mutable digit.
 */
class ItemDigit : public ItemNumber {
private:

    /// Pointer to items declaration
    DeclarationNumber* mDeclaration = nullptr;

public:
    ItemDigit(Game *game,DeclarationNumber *dec,wxXmlNode& node);

    ///  Default constructor (disabled)
    ItemDigit() = delete;

    ///  Copy constructor (disabled)
    ItemDigit(const ItemDigit &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override
    {
        ItemNumber::Accept(visitor);
        visitor->VisitDigit(this);
    }
};

#endif //PROJECT1_GAMELIB_ITEMDIGIT_H
