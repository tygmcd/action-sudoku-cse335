/**
 * @file ItemBackground.h
 * @author Connor Blackmer
 *
 * Class which describes the background, derived from Item
 */

#ifndef PROJECT1_GAMELIB_ITEMBACKGROUND_H
#define PROJECT1_GAMELIB_ITEMBACKGROUND_H

#include "Item.h"
#include "DeclarationBackground.h"

/**
 * Class describing the background
 */
class ItemBackground : public Item {
private:

    /// Pointer to item's decalration
    DeclarationBackground* mDeclaration = nullptr;

public:
	ItemBackground(Game *game,DeclarationBackground *dec,wxXmlNode& node);

    ///  Default constructor (disabled)
    ItemBackground() = delete;

    ///  Copy constructor (disabled)
    ItemBackground(const ItemBackground &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitBackground(this); }
};

#endif //PROJECT1_GAMELIB_ITEMBACKGROUND_H
