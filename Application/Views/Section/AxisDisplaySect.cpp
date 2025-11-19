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
    for(int i = 0; i < 2; i++) {
        axis_sel[i] = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
        axis_sel[i]->SetSelection(i % 2 ? y_axis : x_axis);
        choiceSizer->Add(axis_sel[i], 1, wxEXPAND, 0);
    }
    auto type_sel = new wxChoice(this, TYPE_CHANGE, wxDefaultPosition, wxDefaultSize, {"stick", "trigger"});
    type_sel->SetSelection(0);
    choiceSizer->Add(type_sel, 1, wxEXPAND, 0);

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

void AxisDisplaySect::UpdatePosition(uint8_t xid, int16_t value) {
    if(GetIdX() == xid) {
        TriggerX->SetValue(value);
        Stick->SetX(value);
    }
    if(GetIdY() == xid) {
        TriggerY->SetValue(value);
        Stick->SetY(value);
    }
}

int AxisDisplaySect::GetIdX() {
    return axis_sel[0]->GetSelection();
}

int AxisDisplaySect::GetIdY() {
    return axis_sel[1]->GetSelection();
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
