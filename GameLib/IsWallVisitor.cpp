/**
 * @file IsWallVisitor.cpp
 * @author Connor Blackmer
 */

#include "pch.h"
#include "IsWallVisitor.h"

/**
 * Visits a wall Item
 * @param wall the wall item we are visiting
 */
void IsWallVisitor::VisitWall(ItemWall * wall){
    mIsWall = true;
}