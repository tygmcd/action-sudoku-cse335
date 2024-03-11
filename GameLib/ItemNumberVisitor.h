/**
 * @file ItemNumberVisitor.h
 * @author Tyler McDonald
 *
 * Class derived from ItemVisitor, visits all Numbers
 */

#ifndef ACTIONSUDOKU_GAMELIB_ITEMNUMBERVISITOR_H
#define ACTIONSUDOKU_GAMELIB_ITEMNUMBERVISITOR_H

#include "ItemVisitor.h"

/**
 * Class derived from ItemVisitor, visits all Numbers
 */
class ItemNumberVisitor : public ItemVisitor {
private:
    /// Current value visited
    int mCurrentValue = 0;

public:
    /**
   `* Visit an ItemNumber object
  ` * @param number The number visited
   `*/
    void VisitNumber(ItemNumber* number) override;

    /**
     * Getter for current value
     * @return int current value
     */
     int GetCurrentValue() { return mCurrentValue; }

};

#endif //ACTIONSUDOKU_GAMELIB_ITEMNUMBERVISITOR_H
