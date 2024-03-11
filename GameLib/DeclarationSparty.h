/**
 * @file DeclarationSparty.h
 * @author Juan Faure
 *
 * Class that represents a Declaration for Sparty
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONSPARTY_H
#define PROJECT1_GAMELIB_DECLARATIONSPARTY_H

#include "Declaration.h"
#include "Item.h"

/**
 * Class that represents a Declaration for Sparty
 */
class DeclarationSparty : public Declaration {
private:
	/// front of the head
	int mFront = 0;

private:
    /// head pivot angle
	double mHeadPivotAngle = 0;
	/// x-head pivot
	int mHeadPivotX = 0;
	///y-head pivot
	int mHeadPivotY = 0;
	/// target x
	int mTargetX = 0;
	/// target y
	int mTargetY = 0;

	/// mouth pivot angle
	double mMouthPivotAngle = 0;
	/// x-mouth pivot
	int mMouthPivotX = 0;
	/// y-mouth pivot
	int mMouthPivotY = 0;

	/// mouth image
	std::unique_ptr<wxImage> mMouthImage;
	/// mouth bitmap
	std::unique_ptr<wxBitmap> mMouthBitmap;

	//Loading in the declarations
	void XmlLoad(const wxXmlNode& node);


public:
    /// Constructor
    DeclarationSparty(Level *level, const wxXmlNode& node);

	/// Default constructor (disabled)
	DeclarationSparty() = delete;

	/// Copy constructor (disabled)
	DeclarationSparty(const DeclarationSparty &) = delete;

	/// Assignment operator
	void operator=(const DeclarationSparty &) = delete;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitSparty(this); }

    /**
     * Getter for Sparty's front attribute
     * @return int front attribute
     */
    int GetFront() const { return mFront; };

    /**
    * Getter for Sparty's head pivot angle attribute
    * @return double head pivot angle (radians)
    */
    double GetHeadPivotAngle()  const { return mHeadPivotAngle; };

    /**
     * Getter for Sparty's head pivot X attribute
     * @return int head pivot X
     */
    int GetHeadPivotX() const { return mHeadPivotX; };

    /**
     * Getter for Sparty's head pivot Y attribute
     * @return int head pivot Y
     */
    int GetHeadPivotY() const { return mHeadPivotY; };

    /**
     * Getter for Sparty's target X attribute
     * @return int target X
     */
    int GetTargetX() const { return mTargetX; };

    /**
     * Getter for Sparty's target Y attribute
     * @return int target Y
     */
    int GetTargetY() const { return mTargetY; };

    /**
     * Getter for Sparty's mouth pivot angle attribute
     * @return double mouth pivot angle
     */
    double GetMouthPivotAngle() const { return mMouthPivotAngle; };

    /**
     * Getter for Sparty's mouth pivot X attribute
     * @return int mouth pivot X
     */
    int GetMouthPivotX() const { return mMouthPivotX; };

    /**
     * Getter for Sparty's mouth pivot Y attribute
     * @return int mouth pivot Y
     */
    int GetMouthPivotY() const { return mMouthPivotY; };

    /**
     * Getter for Sparty's mouth bitmap
     * @return pointer to wxBitmap
     */
    wxBitmap* GetMouthBitmap() { return mMouthBitmap.get(); }

    std::shared_ptr<Item> Create(wxXmlNode& node) override;

};

#endif //PROJECT1_GAMELIB_DECLARATIONSPARTY_H
