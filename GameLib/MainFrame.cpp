/**
 * @file MainFrame.cpp
 * @author Tyler McDonald
 */

#include "pch.h"
#include "MainFrame.h"
#include "ids.h"
#include "GameView.h"

///The text to display in the about popup
const std::string AboutText = "Created by Team Ananke";

///The caption to display in the about popup
const std::string AboutCaption = "ActionSudoku: Project 1";

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Action Sudoku",
           wxDefaultPosition,  wxSize( 1200,900 ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    mGameView = new GameView();
    mGameView->Initialize(this);

    // Add it to the sizer
    sizer->Add(mGameView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    auto menuBar = new wxMenuBar( );

    auto fileMenu = new wxMenu();
    auto helpMenu = new wxMenu();
    auto levelMenu = new wxMenu();

    fileMenu->Append(IDM_SOLVE, L"&Solve", "Solve the puzzle");
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    levelMenu->Append(IDM_LEVEL0, L"&Level 0", "Start Level 0");
    levelMenu->Append(IDM_LEVEL1, L"&Level 1", "Start Level 1");
    levelMenu->Append(IDM_LEVEL2, L"&Level 2", "Start Level 2");
    levelMenu->Append(IDM_LEVEL3, L"&Level 3", "Start Level 3");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");


    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"&Level" );
    menuBar->Append(helpMenu, L"&Help" );

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

    SetMenuBar( menuBar );
    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * About menu option handlers
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox(AboutText,
                 AboutCaption,
                 wxOK,
                 this);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mGameView->Stop();
    Destroy();
}
