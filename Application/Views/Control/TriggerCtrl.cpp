#include "TriggerCtrl.hpp"

TriggerCtrl::TriggerCtrl(wxWindow *parent, bool bidirectional)
: AxisCtrl(parent, wxSize(-1, 30)), bidirectional(bidirectional) {}

void TriggerCtrl::Draw(wxDC &dc) {
    wxSize size = GetClientSize();
    int width = size.GetWidth();
    int height = size.GetHeight();
    int value = GetX();

    dc.SetBackground(wxBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE)));
    dc.Clear();

    int range = max_value - min_value;
    double zeroPosRatio = double(-min_value) / range;
    int zeroX = width * zeroPosRatio;

    dc.SetBrush(wxBrush(wxColour(220, 220, 220)));
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(0, 0, width, height);

    double valueRatio = static_cast<double>(value - min_value) / range;
    int progressX = static_cast<int>(width * valueRatio);

    dc.SetPen(*wxBLACK_PEN);
    if(!bidirectional) {
        dc.SetBrush(*wxGREY_BRUSH);
        dc.DrawRectangle(0, 0, progressX, height);
    } else if(value > 0) {
        dc.SetBrush(*wxBLUE_BRUSH);
        dc.DrawRectangle(zeroX, 0, progressX - zeroX, height);
    } else if(value < 0) {
        dc.SetBrush(*wxRED_BRUSH);
        dc.DrawRectangle(progressX, 0, zeroX - progressX, height);
    }

    if(dead_zone > 0) {
        DrawDeadZone(dc, progressX, width, height);
    }

    wxString label = wxString::Format(wxT("%d"), value);
    dc.SetTextForeground(*wxWHITE);
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawLabel(label, wxRect(0, 0, width, height), wxALIGN_CENTER);
}

void TriggerCtrl::DrawDeadZone(wxDC &dc, int progressX, int width, int height) {
    int range = max_value - min_value;
    int deadZoneStartX = width * double(-dead_zone - min_value) / range;
    int deadZoneEndX = width * double(dead_zone - min_value) / range;
    int deadZoneWidth = deadZoneEndX - deadZoneStartX;
    if(!bidirectional) {
        deadZoneStartX = 0;
        deadZoneEndX = deadZoneWidth;
    }

    // wxBrush hatchBrush(wxColour(180, 180, 180), wxBRUSHSTYLE_FDIAGONAL_HATCH);
    // dc.SetBrush(hatchBrush);
    // dc.SetPen(*wxTRANSPARENT_PEN);
    // dc.DrawRectangle(deadZoneStartX, 0, deadZoneEndX - deadZoneStartX, height);

    int lineThickness = 2;
    int spacing = 8;
    wxPen hatchPen(wxColour(160, 160, 160), lineThickness);
    dc.SetPen(hatchPen);
    for(int i = -height; i < deadZoneWidth; i += spacing) {
        dc.DrawLine(i, deadZoneStartX + height, deadZoneStartX + i + height, 0);
    }
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(wxBrush(wxColour(220, 220, 220)));
    dc.DrawRectangle(deadZoneStartX, 0, -height, height);
    dc.DrawRectangle(deadZoneEndX, 0, height, height);

    dc.SetPen(*wxBLACK_PEN);
    if(!bidirectional) {
        if(progressX > deadZoneEndX) {
            dc.SetBrush(*wxGREY_BRUSH);
            dc.DrawRectangle(deadZoneEndX, 0, progressX - deadZoneEndX, height);
        }
    } else if(progressX < deadZoneStartX) {
        dc.SetBrush(*wxRED_BRUSH);
        dc.DrawRectangle(deadZoneStartX, 0, -(deadZoneStartX - progressX)+1, height);
    } else if(progressX > deadZoneEndX) {
        dc.SetBrush(*wxBLUE_BRUSH);
        dc.DrawRectangle(deadZoneEndX, 0, progressX - deadZoneEndX, height);
    }

    dc.SetPen(hatchPen);
    dc.DrawLine(deadZoneStartX, 0, deadZoneStartX, height);
    dc.DrawLine(deadZoneEndX, 0, deadZoneEndX, height);
    dc.DrawLine(deadZoneStartX, 0, deadZoneEndX, 0);
    dc.DrawLine(deadZoneStartX, height, deadZoneEndX, height);
}