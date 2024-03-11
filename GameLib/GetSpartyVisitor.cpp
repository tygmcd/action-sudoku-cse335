/**
 * @file GetSpartyVisitor.cpp
 * @author Tyler McDonald
 */

#include "pch.h"
#include "GetSpartyVisitor.h"


/**
 * Visit a DeclarationSparty object
 * @param sparty Sparty we are visiting
 */
void GetSpartyVisitor::VisitSparty(ItemSparty* sparty)
{
    mFoundSparty = sparty;
}