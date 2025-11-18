/**
 * @file TriggerPanel.hpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __TRIGGERPANEL__
#define __TRIGGERPANEL__

#include <wx/wx.h>

class TriggerPanel : public wxControl {
  public:
    TriggerPanel(wxWindow *parent, bool bidirectional);
    void SetValue(int val);
    int GetValue();
    void SetRange(int min, int max);
    void SetDeadZone(int val);

  private:
    int value = 0;
    int min_value = -32768;
    int max_value = 32767;
    int dead_zone = max_value/4;
    bool bidirectional;

    void OnPaint(wxPaintEvent &event);
    void OnSize(wxSizeEvent &event);
    void Draw(wxDC &dc);
    void DrawDeadZone(wxDC &dc, int progressX, int width, int height);
};

#endif // __TRIGGERPANEL__