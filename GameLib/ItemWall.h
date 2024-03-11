/**
 * @file ItemWall.h
 * @author Connor Blackmer
 *
 *
 */

#ifndef PROJECT1_GAMELIB_ITEMWALL_H
#define PROJECT1_GAMELIB_ITEMWALL_H

#include "Item.h"
#include "DeclarationWall.h"

/**
 * Class which describes a wall Item
 */
class ItemWall : public Item {
private:
    /// Holds the declaration that references this item
    DeclarationWall * mDeclaration = nullptr;

public:
    ItemWall(Game *game, DeclarationWall * dec, wxXmlNode& node);

    ///  Default constructor (disabled)
    ItemWall() = delete;

    ///  Copy constructor (disabled)
    ItemWall(const ItemWall &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override { visitor->VisitWall(this); }
};

#endif //PROJECT1_GAMELIB_ITEMWALL_H
