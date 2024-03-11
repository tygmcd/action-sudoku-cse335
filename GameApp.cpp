/**
 * @file GameApp.cpp
 * @author Tyler McDonald
 */

#include "pch.h"
#include "GameApp.h"
#include <MainFrame.h>

/**
 * Initialize the application.
 * @return
 */
bool GameApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->SetIcon(wxIcon("aaaaaaaa"));
    frame->Show(true);

    return true;
}
