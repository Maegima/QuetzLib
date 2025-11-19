/**
 * @file GamepadSect.hpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-16
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __GAMEPADSECT__
#define __GAMEPADSECT__

#include <wx/wx.h>
#include <wx/tglbtn.h>
#include "Models/Gamepad.hpp"
#include "Views/Section/AxisDisplaySect.hpp"

class GamepadSect : public wxPanel {
  private:
    Gamepad controller;

  public:
    std::vector<wxToggleButton *> hats;
    std::vector<wxToggleButton *> buttons;
    std::vector<AxisDisplaySect *> axes;

    GamepadSect(wxWindow *parent, SDL_JoystickID id);
    SDL_JoystickID Id();
    SDL_Gamepad *GetGamepad();
    void SetAxis(uint8_t xid, int16_t value);
};

#endif // __GAMEPADSECT__