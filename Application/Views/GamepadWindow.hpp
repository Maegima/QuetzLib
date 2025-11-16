/**
 * @file GamepadWindow.hpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-16
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __GAMEPADWINDOW__
#define __GAMEPADWINDOW__

#include <wx/wx.h>
#include <wx/timer.h>
#include <wx/tglbtn.h>
#include "GamepadPanel.hpp"
#include <map>

class GamepadWindow : public wxFrame {
  private:
    wxWindow *parent;
    wxTimer input_timer;
    bool started;
    std::map<SDL_JoystickID, GamepadPanel*> controllers;

    enum EVENTS { TIMER = 4000 };

    void ReadInputs(wxTimerEvent &event);
  public:
    GamepadWindow(wxWindow *parent);
    ~GamepadWindow();
};

#endif // __GAMEPADWINDOW__