/**
 * @file ItemNumberVisitor.cpp
 * @author Tyler McDonald
 */

#include "pch.h"
#include "ItemNumberVisitor.h"
#include "ItemNumber.h"

void ItemNumberVisitor::VisitNumber(ItemNumber* number)
{
    mCurrentValue = number->GetNumberDeclaration()->GetValue();
}
