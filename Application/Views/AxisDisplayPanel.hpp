/**
 * @file AxisDisplayPanel.hpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-14
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __AXISDISPLAYPANEL__
#define __AXISDISPLAYPANEL__

#include <wx/wx.h>

class AxisDisplayPanel : public wxPanel {
  public:
    void last();
    AxisDisplayPanel(wxWindow *parent);
    void UpdatePosition(int x, int y);

  private:
    void OnPaint(wxPaintEvent &event);
    void OnSize(wxSizeEvent &event);
    void OnKeyPress(wxKeyEvent &event);
    int pos_x = 0;
    int pos_y = 0;
    int color = 0;
};

#endif //__AXISDISPLAYPANEL__