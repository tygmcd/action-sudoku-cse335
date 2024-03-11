/**
 * @file ItemDigitVisitor.cpp
 * @author Tyler McDonald
 */

#include "pch.h"
#include "ItemDigitVisitor.h"
#include "ItemDigit.h"

/**
 * Visits a digit, sets isEatable boolean to true
 * @param digit pointer to ItemDigit
 */
void ItemDigitVisitor::VisitDigit(ItemDigit* digit)
{
    mIsEatable = true;

}
