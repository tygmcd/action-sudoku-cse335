/**
 * @file NumberDeclarationValueVisitor.cpp
 * @author Walker McDonald
 */

#include "pch.h"
#include "NumberDeclarationValueVisitor.h"

void NumberDeclarationValueVisitor::VisitNumber(DeclarationNumber *number)
{
    mNumberValue += number->GetValue();
}
