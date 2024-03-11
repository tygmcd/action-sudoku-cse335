/**
 * @file DeclarationGiven.h
 * @author Juan Faure
 *
 * Contains declaration for the DeclarationGiven class, derived from Declaration
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONGIVEN_H
#define PROJECT1_GAMELIB_DECLARATIONGIVEN_H

#include "DeclarationNumber.h"

/**
 * Class that represents a Declaration for a Given number
 */
class DeclarationGiven : public DeclarationNumber {
private:

public:

	/// Default constructor (disabled)
	DeclarationGiven() = delete;

	/// Copy constructor (disabled)
	DeclarationGiven(const DeclarationGiven &) = delete;

	/// Assignment operator
	void operator=(const DeclarationGiven &) = delete;

    DeclarationGiven(Level* level, const wxXmlNode& node);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(DeclarationVisitor* visitor) override
    {
        DeclarationNumber::Accept(visitor); //Upcall
        visitor->VisitGiven(this);
    }

    std::shared_ptr<Item> Create(wxXmlNode& node) override;

};

#endif //PROJECT1_GAMELIB_DECLARATIONGIVEN_H
