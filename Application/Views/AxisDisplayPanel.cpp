#include "AxisDisplayPanel.hpp"
#include <wx/dcbuffer.h>

AxisDisplayPanel::AxisDisplayPanel(wxWindow *parent)
: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(80, 80), wxBORDER_SUNKEN) {
    SetBackgroundStyle(wxBG_STYLE_PAINT); // Indicate the control is user-painted
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUBAR));
    Bind(wxEVT_PAINT, &AxisDisplayPanel::OnPaint, this);
    Bind(wxEVT_SIZE, &AxisDisplayPanel::OnSize, this);
    Bind(wxEVT_KEY_DOWN, &AxisDisplayPanel::OnKeyPress, this);
}

void AxisDisplayPanel::UpdatePosition(int x, int y) {
    pos_x = x;
    pos_y = y;
    Refresh();
}
void AxisDisplayPanel::OnPaint(wxPaintEvent &event) {
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxSize size = GetClientSize();
    int centerX = size.GetX() / 2;
    int centerY = size.GetY() / 2;
    int radius = std::min(centerX, centerY) - 10;

    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.SetPen(*wxBLACK_PEN);
    dc.DrawCircle(centerX, centerY, radius);

    int innerX = centerX + (int)((double)pos_x * radius / 32768.0);
    int innerY = centerY + (int)((double)pos_y * radius / 32768.0);
    printf("inner %d %d ref %d %d\n", innerX, innerY, pos_x, pos_y);
    dc.SetBrush(*wxBLUE_BRUSH);
    dc.DrawCircle(innerX, innerY, 10);
}

void AxisDisplayPanel::OnSize(wxSizeEvent &event) {
    Refresh();
    event.Skip();
}

void AxisDisplayPanel::OnKeyPress(wxKeyEvent &event) {
    if (event.GetKeyCode() == WXK_LEFT) {
        color = (color + 1) % wxSYS_COLOUR_MAX;
        SetBackgroundColour(wxSystemSettings::GetColour((wxSystemColour)color));
    }
    if (event.GetKeyCode() == WXK_RIGHT) {
        color = (color + wxSYS_COLOUR_MAX - 1) % wxSYS_COLOUR_MAX;
        SetBackgroundColour(wxSystemSettings::GetColour((wxSystemColour)color));
    }
    std::cout << color << "\n";
    Refresh();
}
