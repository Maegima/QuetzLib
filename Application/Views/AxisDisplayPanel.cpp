#include "AxisDisplayPanel.hpp"
#include <wx/dcbuffer.h>

AxisDisplayPanel::AxisDisplayPanel(wxWindow *parent, int axes, int x_axis, int y_axis)
: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN) {
    AxisPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(80, 80));
    AxisPanel->SetBackgroundStyle(wxBG_STYLE_PAINT); // Indicate the control is user-painted
    AxisPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUBAR));
    AxisPanel->Bind(wxEVT_PAINT, &AxisDisplayPanel::OnPaint, this);
    AxisPanel->Bind(wxEVT_SIZE, &AxisDisplayPanel::OnSize, this);
    AxisPanel->Bind(wxEVT_KEY_DOWN, &AxisDisplayPanel::OnKeyPress, this);
    Bind(wxEVT_CHOICE, &AxisDisplayPanel::OnChangeType, this, TYPE_CHANGE);

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

    TriggerX = new TriggerPanel(this, true);
    TriggerX->Hide();

    TriggerY = new TriggerPanel(this, true);
    TriggerY->Hide();

    auto sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(choiceSizer, 0, wxALL | wxEXPAND, 1);
    sizer->Add(AxisPanel, 0, wxALL | wxEXPAND, 1);
    sizer->Add(TriggerX, 0, wxALL | wxEXPAND, 1);
    sizer->Add(TriggerY, 0, wxALL | wxEXPAND, 1);
    SetSizer(sizer);
}

void AxisDisplayPanel::UpdatePosition(int x, int y) {
    pos_x = x;
    pos_y = y;
    TriggerX->SetValue(x);
    TriggerY->SetValue(y);
    Refresh();
}
void AxisDisplayPanel::OnPaint(wxPaintEvent &event) {
    wxAutoBufferedPaintDC dc(AxisPanel);
    dc.Clear();

    wxSize size = AxisPanel->GetClientSize();
    int centerX = size.GetX() / 2;
    int centerY = size.GetY() / 2;
    int radius = std::min(centerX, centerY) - 10;

    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.SetPen(*wxBLACK_PEN);
    dc.DrawCircle(centerX, centerY, radius);

    int innerX = centerX + (int)((double)pos_x * radius / 32768.0);
    int innerY = centerY + (int)((double)pos_y * radius / 32768.0);
    dc.SetBrush(*wxBLUE_BRUSH);
    dc.DrawCircle(innerX, innerY, 10);
}

void AxisDisplayPanel::OnSize(wxSizeEvent &event) {
    AxisPanel->Refresh();
    event.Skip();
}

void AxisDisplayPanel::OnKeyPress(wxKeyEvent &event) {
    if (event.GetKeyCode() == WXK_LEFT) {
        color = (color + 1) % wxSYS_COLOUR_MAX;
        AxisPanel->SetBackgroundColour(wxSystemSettings::GetColour((wxSystemColour)color));
    }
    if (event.GetKeyCode() == WXK_RIGHT) {
        color = (color + wxSYS_COLOUR_MAX - 1) % wxSYS_COLOUR_MAX;
        AxisPanel->SetBackgroundColour(wxSystemSettings::GetColour((wxSystemColour)color));
    }
    AxisPanel->Refresh();
}

void AxisDisplayPanel::OnChangeType(wxCommandEvent &event) {
    long sel = event.GetSelection();
    if(sel == 0) {
        AxisPanel->Show();
        TriggerY->Hide();
        TriggerX->Hide();
    } else {
        TriggerX->Show();
        TriggerY->Show();
        AxisPanel->Hide();
    }
    auto sizer = GetSizer();
    sizer->Layout();
    auto conSizer = GetContainingSizer();
    if(conSizer) {
        conSizer->Layout();
    }
}
