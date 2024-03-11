/**
 * @file ids.h
 * @author Tyler McDonald
 *
 * ID values for our program.
 */

#ifndef PROJECT1_GAMELIB_IDS_H
#define PROJECT1_GAMELIB_IDS_H

#include <wx/wx.h>

/**
 * Enum used to create wxIDs for various menu options
 */
enum IDs {
    IDM_LEVEL0 = wxID_HIGHEST + 1,
    IDM_LEVEL1 = wxID_HIGHEST+ 2,
    IDM_LEVEL2 = wxID_HIGHEST + 3,
    IDM_LEVEL3 = wxID_HIGHEST +4,
    IDM_SOLVE = wxID_HIGHEST + 5,
};

#endif //PROJECT1_GAMELIB_IDS_H
