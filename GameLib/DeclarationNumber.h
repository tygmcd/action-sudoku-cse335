/**
 * @file DeclarationNumber.h
 * @author Juan Faure
 *
 *
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONNUMBER_H
#define PROJECT1_GAMELIB_DECLARATIONNUMBER_H

#include "Declaration.h"


/**
 * base class for all Declaration numbers
 */
class DeclarationNumber : public Declaration {
private:
    /// The value of this number
    int mValue = 0;

    void XmlLoad(const wxXmlNode& node);
public:
	/// Default constructor (disabled)
	DeclarationNumber() = delete;

	/// Copy constructor (disabled)
	DeclarationNumber(const DeclarationNumber &) = delete;

	/// Assignment operator
	void operator=(const DeclarationNumber &) = delete;

    /**
     * Getter for the number's value
     * @return The value of the number
     */
    int GetValue()
    {
         return mValue;
    }

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitNumber(this); }

protected:
    DeclarationNumber(Level *level, const wxXmlNode &node);

};

#endif //PROJECT1_GAMELIB_DECLARATIONNUMBER_H
