#include "GamepadWindow.hpp"

GamepadWindow::GamepadWindow(wxWindow *parent)
: wxFrame(parent, wxID_ANY, "Gamepad", wxDefaultPosition, wxSize(1200, 800)),
  parent(parent),
  input_timer(this, TIMER) {
    Bind(wxEVT_TIMER, &GamepadWindow::ReadInputs, this, TIMER);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    if ((started = SDL_Init(SDL_INIT_GAMEPAD | SDL_INIT_SENSOR))) {
        int count;
        SDL_JoystickID *ids = SDL_GetGamepads(&count);
        for (int i = 0; i < count; i++) {
            try {
                auto gp = new GamepadPanel(this, ids[i]);
                controllers.insert({ids[i], gp});
                sizer->Add(gp, 0, wxEXPAND | wxALL, 0);
            } catch (std::ios_base::failure &e) {
                wxLogError("Failed to open Gamepad %u: %s", ids[i], e.what());
            }
        }
        SDL_free(ids);
        input_timer.Start(100);
    } else {
        wxLogError("SDL could not initialize! SDL Error: %s", SDL_GetError());
    }
    SetSizer(sizer);
}

GamepadWindow::~GamepadWindow() {
    input_timer.Stop();
    for (const auto &ctrl : controllers) {
        if (ctrl.second) delete ctrl.second;
    }
    if (started) SDL_Quit();
}

void GamepadWindow::ReadInputs(wxTimerEvent &event) {
    SDL_Event ctrl_event;
    while (SDL_PollEvent(&ctrl_event)) {
        if (ctrl_event.type == SDL_EVENT_QUIT) {
            input_timer.Stop();
            parent->Close();
        } else if (ctrl_event.type == SDL_EVENT_GAMEPAD_ADDED) {
            if (!controllers.contains(ctrl_event.gdevice.which)) {
                auto gp = new GamepadPanel(this, ctrl_event.gdevice.which);
                GetSizer()->Add(gp, 0, wxEXPAND | wxALL, 0);
                GetSizer()->Layout();
                controllers.insert({ctrl_event.gdevice.which, gp});
                std::cout << "Gamepad connected: " << SDL_GetGamepadName(gp->GetGamepad()) << "\n";
                Refresh();
            }
        }
        auto id = ctrl_event.gdevice.which;
        if (controllers.contains(id)) {
            auto gp = controllers[id];
            Uint8 bt;
            int16_t axis, pos;
            Uint8 xid, xid_other;
            switch (ctrl_event.type) {
            case SDL_EVENT_JOYSTICK_BUTTON_UP:
            case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
                bt = ctrl_event.jbutton.button;
                if (bt < gp->buttons.size()) {
                    gp->buttons[bt]->SetValue(SDL_EVENT_JOYSTICK_BUTTON_DOWN == ctrl_event.type);
                }
                break;

            case SDL_EVENT_JOYSTICK_HAT_MOTION:
                bt = ctrl_event.jhat.value;
                for (uint i = 0; i < gp->hats.size(); i++) {
                    gp->hats[i]->SetValue((bt >> i) & 1);
                }
                break;

            case SDL_EVENT_JOYSTICK_AXIS_MOTION:
                axis = ctrl_event.jaxis.value;
                std::cout << (int)ctrl_event.jaxis.axis << " " << axis << "\n";
                xid = ctrl_event.jaxis.axis;
                xid_other = xid % 2 == 0 ? xid + 1 : xid - 1;
                pos = SDL_GetJoystickAxis(SDL_GetJoystickFromID(id), xid_other);
                if (xid % 2 == 0) {
                    gp->axes[xid / 2]->UpdatePosition(axis, pos);
                } else {
                    gp->axes[xid / 2]->UpdatePosition(pos, axis);
                }
                break;

            case SDL_EVENT_GAMEPAD_REMOVED:
                std::cout << "Gamepad disconnected: " << SDL_GetGamepadName(gp->GetGamepad()) << "\n";
                SDL_CloseGamepad(gp->GetGamepad());
                delete controllers[id];
                controllers[id] = nullptr;
                controllers.erase(id);
                break;
            }
        }
    }
}
