/**
 * @file DeclarationXray.h
 * @author Juan Faure
 *
 * Class that represents a Declaration for x-ray
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONXRAY_H
#define PROJECT1_GAMELIB_DECLARATIONXRAY_H

#include "Declaration.h"
#include "Item.h"
/**
 * Class that represents a Declaration for x-ray
 */
class DeclarationXray : public Declaration {
private:
	/// capacity of the xray
	int mCapacity = 0;

	/// loads the XML objects
	void XmlLoad(const wxXmlNode& node);


public:
	/// Default constructor (disabled)
	DeclarationXray() = delete;
	
	/// Copy constructor (disabled)
	DeclarationXray(const DeclarationXray &) = delete;
	
	/// Assignment operator
	void operator=(const DeclarationXray &) = delete;

    DeclarationXray(Level *level, const wxXmlNode& node);

	std::shared_ptr<Item> Create(wxXmlNode& node) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitXray(this); }

    /**
     * Gets capacity from the xml
     * @return Max capacity
     */
    int GetCapacity() {return mCapacity;}
};

#endif //PROJECT1_GAMELIB_DECLARATIONXRAY_H
