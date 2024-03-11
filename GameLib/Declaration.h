/**
 * @file Declaration.h
 * @author Juan Faure
 *
 *
 */

#ifndef PROJECT1_GAMELIB_DECLARATION_H
#define PROJECT1_GAMELIB_DECLARATION_H


#include <memory>
#include "DeclarationVisitor.h"

class Item;
class Level;

/**
 * Declaration class
 */
class Declaration {
private:
	/// The level this Declaration is contained in. using a regular pointer since its not dynamically allocated
	Level  *mLevel;

	/// Id for the declarations
    wxString mID;

	/// X location for the center of the declaration
	double  mX = 0;

	/// Y location for the center of the declaration
	double  mY = 0;

	/// height of the declaration
	int mHeight = 0;

	/// width of the declaration
	int mWidth = 0;

	/// The primary image
	std::unique_ptr<wxImage> mItemImage;

	/// The primary bitmap
	std::unique_ptr<wxBitmap> mItemBitmap;

	/// Function for loading in the XML
    void XmlLoad(const wxXmlNode& node);

public:
    /// destructor
	virtual ~Declaration();

	/// Default constructor (disabled)
	Declaration() = delete;

	/// Copy constructor (disabled)
	Declaration(const Declaration &) = delete;

	/// Assignment operator
	void operator=(const Declaration &) = delete;

	/// getters
	/**
    * The X location of the Declaration
    * @return X location in pixels
    */
	double GetX() const { return mX; }

	/**
	 * The Y location of the declaration
	 * @return Y location in pixels
	 */
	double GetY() const { return mY; }

	/**
    * Grabs the width of the declarations
    * @return width of the declaration
    */
	int GetWidth() const { return mWidth; }

	/**
	 * Grabs the height of the declarations
	 * @return height of the declaration
	 */
	int GetHeight() const { return mHeight; }

	/**
	 * The gets the ID of the declaration object
	 * @return ID as a cosntant string
	 */
	wxString GetID() const { return mID; }

	/**
     * Gets the level for the Declarations
     * @return member pointer to level
     */
	Level *GetLevel(){return mLevel;}

    /**
     * Getter for Item's primary bitmap
     * @return Pointer to wxBitmap
     */
    wxBitmap* GetBitmap() { return mItemBitmap.get(); }

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    virtual void Accept(DeclarationVisitor* visitor) = 0;

    /**
     * Creates an item using XML node
     * @param node XML node
     * @return created item
     */
    virtual std::shared_ptr<Item> Create(wxXmlNode& node) = 0;

protected:
	/// new constructor that will be easier to construct on inheritance
	Declaration(Level *level, const wxXmlNode& node);
};

#endif //PROJECT1_GAMELIB_DECLARATION_H
