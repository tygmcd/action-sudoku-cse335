/**
 * @file Item.h
 * @author Connor Blackmer
 *
 * Base class for the items in our game
 */

#ifndef PROJECT1_GAMELIB_ITEM_H
#define PROJECT1_GAMELIB_ITEM_H

#include "ItemVisitor.h"
#include "Declaration.h"

class Game;

/**
 * Acts as a base class for any items in our game
 */
class Item {
private:
    /// Game the items are contained in
     Game* mGame;

    /// X coordinate for the center of the item
    double mX = 0;

    /// Y coordinate for the center of the item
    double mY = 0;

    /// ID of the item
    std::wstring mID;

    ///Pointer to its declaration
    Declaration *mDeclaration;

protected:
	Item(Game *game,Declaration *dec,wxXmlNode& node);

public:
    ///Default constructor (disabled)
    Item() = delete;

    ///  Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Destructor
    virtual ~Item();

    /**  The X location of the center of the item
    * @return X location in pixels */
    double GetX() const { return mX; }

    /**  The Y location of the center of the item
    * @return Y location in pixels */
    double GetY() const { return mY; }

    /**
     * The ID of the item
     * @return ID of the item
     */
    std::wstring GetID() const{ return mID;}

    /**  Set the item location
    * @param x X location
    * @param y Y location */
    virtual void SetLocation(double x, double y) { mX = x; mY = y; }

    /**
    * Get the declaration for the Item
    * @return Declaration of the item
    */
    Declaration* GetDeclaration() {return mDeclaration;}

    /**
     * Virtual function used to draw items in Game
     * Should be overridden by derived classes
     * @param graphics graphics context used
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) {};

	/// hit test function for checking if the mouse clicks register
	bool HitTest(int x, int y);

	/**
	 * Gets the width of the item
	 * @return double which will be the width of the item
	 */
	double GetWidth() { return mDeclaration->GetWidth(); }

	/**
	 * Gets the height of the item
	 * @return double which will be the height of the item
	 */
	double GetHeight() {return mDeclaration->GetHeight(); }

    /**
     * Gets main Game object
     * @return mGame
     */
    Game* GetGame() { return mGame; }

    /**
     * Virtual Update function for items
     * Should be overridden by derived classes
     * Should only be needed for Sparty's animations
     * @param elapsed Time between updates
     */
    virtual void Update(double elapsed) {}

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    virtual void Accept(ItemVisitor* visitor) = 0;


    bool CanEat(int spartyX, int spartyY);
    bool CanHeadbutt(int spartyX, int spartyY);

    void XmlLoad(const wxXmlNode& node);

};

#endif //PROJECT1_GAMELIB_ITEM_H
