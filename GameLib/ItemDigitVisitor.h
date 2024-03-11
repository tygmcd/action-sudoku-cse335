/**
 * @file ItemDigitVisitor.h
 * @author Tyler McDonald
 *
 * Class inherited from ItemVisitor. Visits a digit, sets boolean to true
 */

#ifndef PROJECT1_GAMELIB_ITEMDIGITVISITOR_H
#define PROJECT1_GAMELIB_ITEMDIGITVISITOR_H

#include "ItemVisitor.h"

/**
 *  Class inherited from ItemVisitor. Visits a digit, sets boolean to true
 */
class ItemDigitVisitor : public ItemVisitor {
private:
    /// Indicates if item is eatable or not
    bool mIsEatable = false;

public:
    void VisitDigit(ItemDigit* digit) override;

    /**
     * Getter for mIsEatable
     * @return boolean mIsEatable
     */
    bool GetEatable() { return mIsEatable; }

};

#endif //PROJECT1_GAMELIB_ITEMDIGITVISITOR_H
