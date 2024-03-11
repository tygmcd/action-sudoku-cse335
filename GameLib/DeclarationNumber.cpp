/**
 * @file DeclarationNumber.cpp
 * @author Juan Faure
 */

#include "pch.h"
#include "DeclarationNumber.h"

/**
 * Constructor
 * @param level The level this declaration is a part of
 * @param node The XML node to load data from
 */
DeclarationNumber::DeclarationNumber(Level *level, const wxXmlNode &node) : Declaration(level, node)
{
    //Default values
    mValue = 0;

    //Load actual values from XML
    XmlLoad(node);
}

/**
 * Load data from XML
 * @param node The XML node to load data from
 */
void DeclarationNumber::XmlLoad(const wxXmlNode& node)
{
    node.GetAttribute("value", "0").ToInt(&mValue);
}

