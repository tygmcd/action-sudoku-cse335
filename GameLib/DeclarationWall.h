/**
 * @file DeclarationWall.h
 * @author Connor Blackmer
 *
 *
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONWALL_H
#define PROJECT1_GAMELIB_DECLARATIONWALL_H

#include "Declaration.h"
#include "Item.h"

/**
 * Declaration Class for a wall
 */
class DeclarationWall : public Declaration {
private:

public:
    /// Default constructor (disabled)
    DeclarationWall() = delete;

    /// Copy constructor (disabled)
    DeclarationWall(const DeclarationWall &) = delete;

    /// Assignment operator
    void operator=(const DeclarationWall &) = delete;

    DeclarationWall(Level *level, const wxXmlNode& node);

    std::shared_ptr<Item> Create(wxXmlNode& node) override;

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitWall(this); }
};

#endif //PROJECT1_GAMELIB_DECLARATIONWALL_H
