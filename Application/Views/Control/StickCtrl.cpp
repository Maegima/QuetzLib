#include "StickCtrl.hpp"

StickCtrl::StickCtrl(wxWindow *parent) : AxisCtrl(parent, wxSize(80, 80)) {
    this->dead_zone = 20000;
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUBAR));
}

void StickCtrl::UpdatePosition(int16_t x, int16_t y) {
    if(this->x != x || this->y != y) {
        this->x = x;
        this->y = y;
        Refresh();
    }
}

void StickCtrl::Draw(wxDC &dc) {
    dc.Clear();

    wxSize size = this->GetClientSize();
    int centerX = size.GetX()/2;
    int centerY = size.GetY()/2;
    int radius = std::min(centerX, centerY)-10;

    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.SetPen(*wxBLACK_PEN);
    dc.DrawCircle(centerX, centerY, radius);
    dc.SetBrush(wxBrush(wxColour(180, 180, 180)));
    dc.SetPen(*wxGREY_PEN);
    dc.DrawCircle(centerX, centerY, (int) radius * (this->dead_zone/32768.0));

    int innerX = centerX+(int)((double)x * radius/32768.0);
    int innerY = centerY+(int)((double)y * radius/32768.0);
    dc.SetBrush(*wxBLUE_BRUSH);
    dc.SetPen(*wxBLACK_PEN);
    dc.DrawCircle(innerX, innerY, 2);
}
