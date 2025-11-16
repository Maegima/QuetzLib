#include "Gamepad.hpp"
#include <ios>

Gamepad::Gamepad(SDL_JoystickID id) {
    gamepad = SDL_OpenGamepad(id);
    if(!gamepad) throw new std::ios_base::failure(SDL_GetError());
    joystick = SDL_GetJoystickFromID(id);
    if(!joystick) throw new std::ios_base::failure(SDL_GetError());
    int size = -1;
    size = SDL_GetNumJoystickHats(joystick);
    if(size == -1) throw new std::ios_base::failure(SDL_GetError());
    hats.resize(size*4, -1);
    size = SDL_GetNumJoystickButtons(joystick);
    if(size == -1) throw new std::ios_base::failure(SDL_GetError());
    buttons.resize(size, -1);
}

Gamepad::~Gamepad() {
    if(gamepad) SDL_CloseGamepad(gamepad);
}



