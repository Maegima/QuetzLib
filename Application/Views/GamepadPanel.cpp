#include "GamepadPanel.hpp"
#include <wx/sizer.h>

GamepadPanel::GamepadPanel(wxWindow *parent, SDL_JoystickID id) : wxPanel(parent), controller(id) {
    wxStaticBoxSizer *firstSection = new wxStaticBoxSizer(wxVERTICAL, this, "&Section1");
    wxStaticBoxSizer *secondSection = new wxStaticBoxSizer(wxVERTICAL, this, "&Section2");
    wxStaticBoxSizer *thirdSection = new wxStaticBoxSizer(wxVERTICAL, this, "&Section3");

    auto fst_box = firstSection->GetStaticBox();
    for (auto &hat : controller.hats) {
        auto bt = new wxToggleButton(fst_box, wxID_ANY, "hat");
        hats.push_back(bt);
        firstSection->Add(bt, 0, wxALL | wxEXPAND, 1);
        hat = hats.size() - 1;
    }
    auto snd_box = secondSection->GetStaticBox();
    for (auto &btt : controller.buttons) {
        auto bt = new wxToggleButton(snd_box, wxID_ANY, "button");
        buttons.push_back(bt);
        secondSection->Add(bt, 0, wxALL | wxEXPAND, 1);
        btt = buttons.size() - 1;
    }
    auto trd_box = thirdSection->GetStaticBox();
    for (uint i = 0; i < controller.axes.size()/2; i++) {
        auto bt = new AxisDisplayPanel(trd_box, controller.axes.size(), 2*axes.size(), 2*axes.size()+1);
        axes.push_back(bt);
        thirdSection->Add(bt, 0, wxALL | wxEXPAND, 1);
        controller.axes[i] = 2*axes.size() - 1;
        controller.axes[i+1] = 2*axes.size();
    }
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(firstSection, 1, wxALL | wxEXPAND, 10);
    sizer->Add(secondSection, 1, wxALL | wxEXPAND, 10);
    sizer->Add(thirdSection, 1, wxALL | wxEXPAND, 10);
    SetSizer(sizer);
}

SDL_JoystickID GamepadPanel::Id() {
    return controller.id;
}

SDL_Gamepad *GamepadPanel::GetGamepad() {
    return controller.gamepad;
}