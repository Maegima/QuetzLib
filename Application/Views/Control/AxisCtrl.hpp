/**
 * @file AxisCtrl.hpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __AXISCTRL__
#define __AXISCTRL__

#include <wx/wx.h>
#include <cstdint>

class AxisCtrl : public wxControl {
  public:
    AxisCtrl(wxWindow *parent,
             const wxSize &size = wxDefaultSize,
             const wxPoint &position = wxDefaultPosition,
             long style = wxBORDER_SUNKEN,
             wxWindowID id = wxID_ANY);
    ~AxisCtrl();
    void SetX(int16_t value);
    int16_t GetX() { return x; }
    void SetY(int16_t value);
    int16_t GetY() { return y; }
    void SetDeadZone(uint16_t dead_zone);

  protected:
    int16_t x;
    int16_t y;
    uint16_t dead_zone;
    virtual void Draw(wxDC &dc) = 0;

  private:
    void OnPaint(wxPaintEvent &event);
    void OnSize(wxSizeEvent &event);
};

#endif // __AXISCTRL__