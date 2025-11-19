/**
 * @file GamepadWind.hpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-16
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __GAMEPADWIND__
#define __GAMEPADWIND__

#include <wx/wx.h>
#include <wx/timer.h>
#include <wx/tglbtn.h>
#include "Views/Section/GamepadSect.hpp"
#include <map>

class GamepadWind : public wxFrame {
  private:
    wxWindow *parent;
    wxTimer input_timer;
    bool started;
    std::map<SDL_JoystickID, GamepadSect*> controllers;

    enum EVENTS { TIMER = 4000 };

    void ReadInputs(wxTimerEvent &event);
  public:
    GamepadWind(wxWindow *parent);
    ~GamepadWind();
};

#endif // __GAMEPADWIND__