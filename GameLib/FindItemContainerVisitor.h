/**
 * @file FindItemContainerVisitor.h
 * @author Tyler McDonald
 *
 * Derived of ItemVisitor, finds and stores the xray object
 */

#ifndef PROJECT1_GAMELIB_FINDITEMCONTAINERVISITOR_H
#define PROJECT1_GAMELIB_FINDITEMCONTAINERVISITOR_H

#include "ItemVisitor.h"
#include "ItemXray.h"
#include "ItemContainer.h"

/**
 * Derived of ItemVisitor, finds and stores the xray object
 */
class FindItemContainerVisitor : public ItemVisitor {
private:
    /// Container Id
    wxString mId;

    /// Found Xray item
    ItemXray* mItemXray = nullptr;

    /// Found Container item
    ItemContainer* mItemContainer = nullptr;

public:
    /**
     * Constructor
     */
     FindItemContainerVisitor () {};

    /**
    * Constructor
     * @param id id of the container
    */
    FindItemContainerVisitor(wxString id) : mId(id) {};

    /**
    * Gets Xray pointer
    * @return Pointer to Xray
    */
    ItemXray* GetItemXray() { return mItemXray; }

    /**
     * Gets Container pointer
     * @return Pointer to Container
     */
     ItemContainer* GetItemContainer() { return mItemContainer; }

    void VisitXray(ItemXray* xray) override;

    void VisitContainer(ItemContainer *container) override;

};

#endif //PROJECT1_GAMELIB_FINDITEMCONTAINERVISITOR_H
