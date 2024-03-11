/**
 * @file DeclarationBackground.h
 * @author Juan Faure
 *
 *
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONBACKGROUND_H
#define PROJECT1_GAMELIB_DECLARATIONBACKGROUND_H


#include "Declaration.h"
#include "Item.h"

/**
 * background declaration for the level
 */
class DeclarationBackground : public Declaration {
private:

public:
    /// Constructor
    DeclarationBackground(Level *level, const wxXmlNode& node);

	/// Default constructor (disabled)
	DeclarationBackground() = delete;

	/// Copy constructor (disabled)
	DeclarationBackground(const DeclarationBackground &) = delete;

	/// Assignment operator
	void operator=(const DeclarationBackground &) = delete;

	/**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitBackground(this); }

    std::shared_ptr<Item> Create(wxXmlNode& node) override;

protected:

};

#endif //PROJECT1_GAMELIB_DECLARATIONBACKGROUND_H
