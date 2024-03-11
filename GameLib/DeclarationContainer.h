/**
 * @file DeclarationContainer.h
 * @author Juan Faure
 *
 *
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONCONTAINER_H
#define PROJECT1_GAMELIB_DECLARATIONCONTAINER_H

#include "Declaration.h"

/**
 * Container for the declarations in the level
 */
class DeclarationContainer : public Declaration {
private:
	/// Secondary image
	std::unique_ptr<wxImage> mItemImage;

	/// Secondary bitmap
	std::unique_ptr<wxBitmap> mContainerBitMap; ///< DeclarationSparty mouth image to use

	//Loading in the declarations
	void XmlLoad(const wxXmlNode& node);


public:
	/// Default constructor (disabled)
	DeclarationContainer() = delete;
	
	/// Copy constructor (disabled)
	DeclarationContainer(const DeclarationContainer &) = delete;
	
	/// Assignment operator
	void operator=(const DeclarationContainer &) = delete;

    DeclarationContainer(Level *level, const wxXmlNode& node);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitContainer(this); }

    /**
    * Getter for secondary bitmap
    * @return Pointer to wxBitmap
    */
    wxBitmap* GetContainerBitmap() { return mContainerBitMap.get(); }

    std::shared_ptr<Item> Create(wxXmlNode& node) override;

};

#endif //PROJECT1_GAMELIB_DECLARATIONCONTAINER_H
