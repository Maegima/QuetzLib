/**
 * @file Gamepad.hpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __GAMEPAD__
#define __GAMEPAD__

#include <SDL3/SDL.h>
#include <vector>

class Gamepad {
  public:
    SDL_JoystickID id;
    std::vector<int> hats;
    std::vector<int> axes;
    std::vector<int> buttons;
    SDL_Gamepad *gamepad;
    SDL_Joystick *joystick;
    Gamepad(SDL_JoystickID id);
    ~Gamepad();
};

#endif // __GAMEPAD__