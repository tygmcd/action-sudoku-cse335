/**
 * @file Declaration.cpp
 * @author Juan Faure
 */

#include "pch.h"
#include "Declaration.h"

using namespace std;

/// String location of the images
const wxString ImageDirectory = "images/";

/**
 * Constructor
 * @param level The level that we will be assigning these objects to
 * @param node The XML node to load data from
 */
Declaration::Declaration(Level *level, const wxXmlNode& node) : mLevel(level)
{
    XmlLoad(node);
}

/**
 * Load the declaration from XML
 * @param node The XML node to load data from
 */
void Declaration::XmlLoad(const wxXmlNode& node)
{
    //Load ID
    mID = node.GetName();

    //Load image filename
    wxString imageFilename = node.GetAttribute(L"image", L"INVALID");
    if (imageFilename == "INVALID")
    {
        imageFilename = node.GetAttribute(L"image1", L"INVALID");
    }

    //Load image
    mItemImage = make_unique<wxImage>(ImageDirectory+imageFilename, wxBITMAP_TYPE_ANY);
    mItemBitmap = make_unique<wxBitmap>(*mItemImage);

    //Load width and height
    node.GetAttribute(L"width", L"0").ToInt(&mWidth);
    node.GetAttribute(L"height", L"0").ToInt(&mHeight);
}

/**
 * Destructor
 * this is made just in case any other objects need to freed up.
 */
Declaration::~Declaration()
{
}