#include "AxisDisplaySect.hpp"
#include <wx/dcbuffer.h>

AxisDisplaySect::AxisDisplaySect(wxWindow *parent, int axes, int x_axis, int y_axis)
: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN) {
    Bind(wxEVT_CHOICE, &AxisDisplaySect::OnChangeType, this, TYPE_CHANGE);

    wxArrayString choices;
    choices.Alloc(axes);
    for(int i = 0; i < axes; i++) {
        choices.Add("axis " + std::to_string(i+1));
    }
    auto choiceSizer = new wxBoxSizer(wxHORIZONTAL);
    fst_axis = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
    fst_axis->SetSelection(x_axis);
    choiceSizer->Add(fst_axis, 1, wxEXPAND, 0);
    snd_axis = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
    snd_axis->SetSelection(y_axis);
    choiceSizer->Add(snd_axis, 1, wxEXPAND, 0);
    sel_type = new wxChoice(this, TYPE_CHANGE, wxDefaultPosition, wxDefaultSize, {"stick", "trigger"});
    sel_type->SetSelection(0);
    choiceSizer->Add(sel_type, 1, wxEXPAND, 0);

    Stick = new StickCtrl(this);

    TriggerX = new TriggerCtrl(this, true);
    TriggerX->Hide();

    TriggerY = new TriggerCtrl(this, true);
    TriggerY->Hide();

    auto sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(choiceSizer, 0, wxALL | wxEXPAND, 1);
    sizer->Add(Stick, 0, wxALL | wxEXPAND, 1);
    sizer->Add(TriggerX, 0, wxALL | wxEXPAND, 1);
    sizer->Add(TriggerY, 0, wxALL | wxEXPAND, 1);
    SetSizer(sizer);
}

void AxisDisplaySect::UpdatePosition(int x, int y) {
    Stick->UpdatePosition(x, y);
    TriggerX->SetValue(x);
    TriggerY->SetValue(y);
    Refresh();
}

void AxisDisplaySect::OnChangeType(wxCommandEvent &event) {
    long sel = event.GetSelection();
    if(sel == 0) {
        Stick->Show();
        TriggerY->Hide();
        TriggerX->Hide();
    } else {
        TriggerX->Show();
        TriggerY->Show();
        Stick->Hide();
    }
    auto sizer = GetSizer();
    sizer->Layout();
    auto conSizer = GetContainingSizer();
    if(conSizer) {
        conSizer->Layout();
    }
}
