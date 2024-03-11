/**
 * @file IsWallVisitor.h
 * @author Connor Blackmer
 *
 * Derived from ItemVisitor, checks to see if an Item is a Wall or not
 */

#ifndef PROJECT1_GAMELIB_ISWALLVISITOR_H
#define PROJECT1_GAMELIB_ISWALLVISITOR_H

#include "ItemVisitor.h"
#include "ItemWall.h"

/**
 * Derived from ItemVisitor, checks to see if an Item is a Wall or not
 */
class IsWallVisitor : public ItemVisitor {
private:
    ///Boolean which knows if item is a wall or not
    bool mIsWall = false;

public:
    /**
     * Returns if an item is a wall
     * @return mIsWall boolean
     */
    bool IsWall(){return mIsWall;}

    void VisitWall(ItemWall * wall) override;
};

#endif //PROJECT1_GAMELIB_ISWALLVISITOR_H
