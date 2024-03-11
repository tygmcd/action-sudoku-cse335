/**
 * @file DeclarationDigit.h
 * @author Juan Faure
 *
 *
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONDIGIT_H
#define PROJECT1_GAMELIB_DECLARATIONDIGIT_H

#include "DeclarationNumber.h"

/**
 * Digit declarations for the numbers
 */
class DeclarationDigit : public DeclarationNumber {
private:

public:
    /// Constructor
    DeclarationDigit(Level* level, const wxXmlNode& node);

	/// Default constructor (disabled)
	DeclarationDigit() = delete;

	/// Copy constructor (disabled)
	DeclarationDigit(const DeclarationDigit &) = delete;

	/// Assignment operator
	void operator=(const DeclarationDigit &) = delete;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(DeclarationVisitor* visitor) override
    {
        DeclarationNumber::Accept(visitor); //Upcall
        visitor->VisitDigit(this);
    }

    std::shared_ptr<Item> Create(wxXmlNode& node) override;
};

#endif //PROJECT1_GAMELIB_DECLARATIONDIGIT_H
