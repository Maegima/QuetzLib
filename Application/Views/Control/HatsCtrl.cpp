#include "HatsCtrl.hpp"
#include "HatsCtrl.hpp"

HatsCtrl::HatsCtrl(wxWindow *parent) : wxPanel(parent, wxID_ANY) {
    auto sizer = new wxGridSizer(3, 3, 2, 2);

    sizer->AddSpacer(0);
    hats[0] = new wxToggleButton(this, wxID_ANY, "Up");
    sizer->Add(hats[0], wxSizerFlags().Expand());
    sizer->AddSpacer(0);
    hats[3] = new wxToggleButton(this, wxID_ANY, "Left");
    sizer->Add(hats[3], wxSizerFlags().Expand());
    sizer->AddSpacer(0);
    hats[1] = new wxToggleButton(this, wxID_ANY, "Right");
    sizer->Add(hats[1], wxSizerFlags().Expand());
    sizer->AddSpacer(0);
    hats[2] = new wxToggleButton(this, wxID_ANY, "Down");
    sizer->Add(hats[2], wxSizerFlags().Expand());
    sizer->AddSpacer(0);

    SetSizerAndFit(sizer);
}

void HatsCtrl::SetValue(uint8_t val) {
    for(int i = 0; i < 4; i++) {
        hats[i]->SetValue((val >> i) & 1);
    }
}
