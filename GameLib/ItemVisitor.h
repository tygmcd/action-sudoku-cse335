/**
 * @file ItemVisitor.h
 * @author Walker McDonald
 *
 * Base class for an Item visitor
 */

#ifndef PROJECT1_GAMELIB_ITEMVISITOR_H
#define PROJECT1_GAMELIB_ITEMVISITOR_H

// Forward references to all item types
class ItemNumber;
class ItemDigit;
class ItemGiven;
class ItemBackground;
class ItemSparty;
class ItemXray;
class ItemContainer;
class ItemWall;

/**
 * Tile visitor base class
 */
class ItemVisitor {
protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
    ItemVisitor() {}

public:
    virtual ~ItemVisitor() {}

    /**
     * Visit a ItemNumber object
     * @param number Number we are visiting
     */
    virtual void VisitNumber(ItemNumber* number) {}

    /**
     * Visit a ItemDigit object
     * @param digit Digit we are visiting
     */
    virtual void VisitDigit(ItemDigit* digit) {}

    /**
     * Visit a ItemGiven object
     * @param given Given we are visiting
     */
    virtual void VisitGiven(ItemGiven* given) {}

    /**
     * Visit a ItemBackground object
     * @param background Background we are visiting
     */
    virtual void VisitBackground(ItemBackground* background) {}

    /**
     * Visit a ItemSparty object
     * @param sparty Sparty we are visiting
     */
    virtual void VisitSparty(ItemSparty* sparty) {}

    /**
     * Visit a ItemXray object
     * @param xray Xray we are visiting
     */
    virtual void VisitXray(ItemXray* xray) {}

    /**
     * Visit a ItemContainer object
     * @param container Container we are visiting
     */
    virtual void VisitContainer(ItemContainer* container) {}

    /**
    * Visit a ItemWall object
    * @param wall Wall we are visiting
    */
    virtual void VisitWall(ItemWall* wall) {}
};

#endif //PROJECT1_GAMELIB_ITEMVISITOR_H
