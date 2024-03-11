/**
 * @file GetSpartyVisitor.h
 * @author Tyler McDonald
 *
 * Concrete Visitor that is used to get Sparty object from
 * Items List
 */

#ifndef PROJECT1_GAMELIB_GETSPARTYVISITOR_H
#define PROJECT1_GAMELIB_GETSPARTYVISITOR_H

#include "ItemVisitor.h"

/**
 * Concrete Visitor that is used to get Sparty object from
 * Items List
 */
class GetSpartyVisitor : public ItemVisitor {
private:
    /// Pointer to the found Sparty
    ItemSparty* mFoundSparty = nullptr;

public:
    /**
     * Constructor
     */
    GetSpartyVisitor() {};

    /**
     * Gets sparty pointer
     * @return Pointer to Sparty
     */
    ItemSparty* GetItemSparty() { return mFoundSparty; }

    virtual void VisitSparty(ItemSparty* sparty) override;

};

#endif //PROJECT1_GAMELIB_GETSPARTYVISITOR_H
