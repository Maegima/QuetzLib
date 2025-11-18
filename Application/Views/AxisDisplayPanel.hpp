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
    AxisDisplayPanel(wxWindow *parent, int axes, int x_axis = 0, int y_axis = 1);
    void UpdatePosition(int x, int y);
    wxChoice *fst_axis;
    wxChoice *snd_axis;
    int pos_x;
    int pos_y;

  private:
    int color = 0;
    wxPanel *AxisPanel;
    void OnPaint(wxPaintEvent &event);
    void OnSize(wxSizeEvent &event);
    void OnKeyPress(wxKeyEvent &event);
    int GetX();
    int GetY();
};

#endif //__AXISDISPLAYPANEL__