/**
 * @file MainFrame.h
 * @author Tyler McDonald
 *
 * The top-level (main) frame of the application
 */

#ifndef PROJECT1_GAMELIB_MAINFRAME_H
#define PROJECT1_GAMELIB_MAINFRAME_H

class GameView;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame {
private:
    /// View class for our Game
    GameView *mGameView;

    void OnClose(wxCloseEvent &event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

public:
    void Initialize();

};

#endif //PROJECT1_GAMELIB_MAINFRAME_H
