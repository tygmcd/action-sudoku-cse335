/**
 * @file NumberDeclarationValueVisitor.h
 * @author Walker McDonald
 *
 * A concrete visitor to get the total value of number declarations
 */

#ifndef PROJECT1_GAMELIB_NUMBERDECLARATIONVALUEVISITOR_H
#define PROJECT1_GAMELIB_NUMBERDECLARATIONVALUEVISITOR_H

#include "DeclarationVisitor.h"
#include "DeclarationNumber.h"

/**
 * A concrete visitor to get the total value of number declarations
 */
class NumberDeclarationValueVisitor : public DeclarationVisitor {
private:
    ///The total value of all number declarations visited
    int mNumberValue = 0;

    /// Current value visited
    int mCurrentValue = 0;

public:
    /**
     * Visits a number object
     * @param number Pointer to number object
     */
    void VisitNumber(DeclarationNumber* number) override;

    /**
     * Get the total value of all number declarations visited
     * @return The total value of all number declarations visited
     */
    int GetValue() { return mNumberValue; }

    /**
     * Gets current number value from visitor
     * @return current number from visitor
     */
     int GetCurrentValue() { return mCurrentValue; }
};

#endif //PROJECT1_GAMELIB_NUMBERDECLARATIONVALUEVISITOR_H
