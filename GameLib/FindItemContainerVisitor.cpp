/**
 * @file FindItemContainerVisitor.cpp
 * @author Tyler McDonald
 */

#include "pch.h"
#include "FindItemContainerVisitor.h"

/**
 * Visit a DeclarationXray object
 * @param xray Xray we are visiting
 */
void FindItemContainerVisitor::VisitXray(ItemXray* xray)
{
    mItemXray = xray;
}

/**
  * Visit a DeclarationContainer object
  * @param container Container we are visiting
  */
void FindItemContainerVisitor::VisitContainer(ItemContainer *container)
{
    if (container->GetID() == mId)
    {
        mItemContainer = container;
    }
}