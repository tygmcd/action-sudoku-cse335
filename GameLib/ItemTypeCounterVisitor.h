/**
 * @file ItemTypeCounterVisitor.h
 * @author Walker McDonald
 *
 * A concrete item visitor that counts the number of each type of item visited
 */

#ifndef PROJECT1_GAMELIB_ITEMTYPECOUNTERVISITOR_H
#define PROJECT1_GAMELIB_ITEMTYPECOUNTERVISITOR_H

#include "ItemVisitor.h"
#include "ItemNumber.h"

/**
 * A concrete item visitor that counts the number of each type of item visited
 */
class ItemTypeCounterVisitor : public ItemVisitor {
private:

    ///The number of ItemBackground objects visited
    int mBackgroundCount = 0;

    ///The number of ItemContainer objects visited
    int mContainerCount = 0;

    ///The number of ItemDigit objects visited
    int mDigitCount = 0;

    ///The number of ItemGiven objects visited
    int mGivenCount = 0;

    ///The number of ItemNumber objects visited (digit + given)
    int mNumberCount = 0;

    ///The number of ItemSparty objects visited
    int mSpartyCount = 0;

    ///The number of ItemXray objects visited
    int mXrayCount = 0;

public:
    /**
     * Visit an ItemBackground object
     * @param background The background visited
     */
    void VisitBackground(ItemBackground* background) override { mBackgroundCount++; }

    /**
     * Visit an ItemContainer object
     * @param container The container visited
     */
    void VisitContainer(ItemContainer* container) override { mContainerCount++; }

    /**
     * Visit an ItemDigit object
     * @param digit The digit visited
     */
    void VisitDigit(ItemDigit* digit) override { mDigitCount++; }

    /**
     * Visit an ItemGiven object
     * @param given The given visited
     */
    void VisitGiven(ItemGiven* given) override { mGivenCount++; }

    /**
     * Visit an ItemNumber object
     * @param number The number visited
     */
    void VisitNumber(ItemNumber* number) override { mNumberCount++;}

    /**
     * Visit an ItemSparty object
     * @param sparty The sparty visited
     */
    void VisitSparty(ItemSparty* sparty) override { mSpartyCount++; }

    /**
     * Visit an ItemXray object
     * @param xray The xray visited
     */
    void VisitXray(ItemXray* xray) override { mXrayCount++; }

    /**
     * Get the number of ItemBackground objects visited
     * @return The number of ItemBackground objects visited
     */
     int GetBackgroundCount() { return mBackgroundCount; }

    /**
    * Get the number of ItemContainer objects visited
    * @return The number of ItemContainer objects visited
    */
    int GetContainerCount() { return mContainerCount; }

    /**
     * Get the number of ItemDigit objects visited
     * @return The number of ItemDigit objects visited
     */
    int GetDigitCount() { return mDigitCount; }

    /**
     * Get the number of ItemGiven objects visited
     * @return The number of ItemGiven objects visited
     */
    int GetGivenCount() { return mGivenCount; }

    /**
     * Get the number of ItemNumber objects visited
     * @return The number of ItemNumber objects visited
     */
    int GetNumberCount() { return mNumberCount; }

    /**
     * Get the number of ItemSparty objects visited
     * @return The number of ItemSparty objects visited
     */
    int GetSpartyCount() { return mSpartyCount; }

    /**
     * Get the number of ItemXray objects visited
     * @return The number of ItemXray objects visited
     */
    int GetXrayCount() { return mXrayCount; }
};

#endif //PROJECT1_GAMELIB_ITEMTYPECOUNTERVISITOR_H
