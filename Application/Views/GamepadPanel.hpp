/**
 * @file GamepadPanel.hpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-16
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __GAMEPADPANEL__
#define __GAMEPADPANEL__

#include <wx/wx.h>
#include <wx/tglbtn.h>
#include "Models/Gamepad.hpp"
#include "AxisDisplayPanel.hpp"

class GamepadPanel : public wxPanel {
  private:
    Gamepad controller;

  public:
    std::vector<wxToggleButton *> hats;
    std::vector<wxToggleButton *> buttons;
    std::vector<AxisDisplayPanel *> axes;

    GamepadPanel(wxWindow *parent, SDL_JoystickID id);
    SDL_JoystickID Id();
    SDL_Gamepad *GetGamepad();
};

#endif // __GAMEPADPANEL__