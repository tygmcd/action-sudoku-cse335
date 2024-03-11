/**
 * @file GetAllDigitsVisitor.h
 * @author Walker McDonald
 *
 * A concrete visitor that gets every digit in the playing area that
 * isn't already in the grid
 */

#ifndef PROJECT1_GAMELIB_GETALLDIGITSVISITOR_H
#define PROJECT1_GAMELIB_GETALLDIGITSVISITOR_H

#include <map>
#include <list>
#include "ItemVisitor.h"

/**
 * A concrete visitor that gets every digit in the playing area that
 * isn't already in the grid
 */
class GetAllDigitsVisitor : public ItemVisitor {
private:
    /// Map of value to Digit item
    std::map<int, std::list<ItemDigit*>> mDigits;

public:
    void VisitDigit(ItemDigit* digit) override;

    ItemDigit* PopDigitOfValue(int value);
};

#endif //PROJECT1_GAMELIB_GETALLDIGITSVISITOR_H
