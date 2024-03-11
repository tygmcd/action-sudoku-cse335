/**
 * @file DeclarationVisitor.h
 * @author Walker McDonald
 *
 * Declaration visitor base class
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONVISITOR_H
#define PROJECT1_GAMELIB_DECLARATIONVISITOR_H

// Forward references to all declaration types
class DeclarationNumber;
class DeclarationDigit;
class DeclarationGiven;
class DeclarationBackground;
class DeclarationSparty;
class DeclarationXray;
class DeclarationContainer;
class DeclarationWall;

/**
 * Tile visitor base class
 */
class DeclarationVisitor {
protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
    DeclarationVisitor() {}

public:
    virtual ~DeclarationVisitor() {}

    /**
     * Visit a DeclarationNumber object
     * @param number Number we are visiting
     */
    virtual void VisitNumber(DeclarationNumber* number) {}

    /**
     * Visit a DeclarationDigit object
     * @param digit Digit we are visiting
     */
    virtual void VisitDigit(DeclarationDigit* digit) {}

    /**
     * Visit a DeclarationGiven object
     * @param given Given we are visiting
     */
    virtual void VisitGiven(DeclarationGiven* given) {}

    /**
     * Visit a DeclarationBackground object
     * @param background Background we are visiting
     */
    virtual void VisitBackground(DeclarationBackground* background) {}

    /**
     * Visit a DeclarationSparty object
     * @param sparty Sparty we are visiting
     */
    virtual void VisitSparty(DeclarationSparty* sparty) {}

    /**
     * Visit a DeclarationXray object
     * @param xray Xray we are visiting
     */
    virtual void VisitXray(DeclarationXray* xray) {}

    /**
     * Visit a DeclarationContainer object
     * @param container Container we are visiting
     */
    virtual void VisitContainer(DeclarationContainer* container) {}

    /**
    * Visit a DeclarationWall object
    * @param wall Wall we are visiting
    */
    virtual void VisitWall(DeclarationWall* wall) {}
};


#endif //PROJECT1_GAMELIB_DECLARATIONVISITOR_H
