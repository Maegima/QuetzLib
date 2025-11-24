#include "AxisCtrl.hpp"
#include <wx/dcbuffer.h>

AxisCtrl::AxisCtrl(wxWindow *parent, const wxSize &size, const wxPoint &position, long style, wxWindowID id)
: wxControl(parent, id, position, size, style) {
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &AxisCtrl::OnPaint, this);
    Bind(wxEVT_SIZE, &AxisCtrl::OnSize, this);
}

AxisCtrl::~AxisCtrl() {}

void AxisCtrl::SetX(int16_t value) {
    if(value != x) {
        x = value;
        Refresh();
    }
}

void AxisCtrl::SetY(int16_t value) {
    if(value != y) {
        y = value;
        Refresh();
    }
}

void AxisCtrl::SetDeadZone(uint16_t dead_zone) {
    if(this->dead_zone != dead_zone) {
        this->dead_zone = dead_zone;
        Refresh();
    }
}

void AxisCtrl::OnPaint(wxPaintEvent &event) {
    wxAutoBufferedPaintDC dc(this);
    Draw(dc);
}

void AxisCtrl::OnSize(wxSizeEvent &event) {
    Refresh();
    event.Skip();
}
