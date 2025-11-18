/**
 * @file AxisDisplayPanel.hpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __AXISDISPLAYPANEL__
#define __AXISDISPLAYPANEL__

#include <wx/wx.h>
#include "TriggerPanel.hpp"

class AxisDisplayPanel : public wxPanel {
  public:
    AxisDisplayPanel(wxWindow *parent, int axes, int x_axis = 0, int y_axis = 1);
    void UpdatePosition(int x, int y);
    wxChoice *fst_axis;
    wxChoice *snd_axis;
    wxChoice *sel_type;
    int pos_x;
    int pos_y;

  private:
    int color = 0;
    wxPanel *AxisPanel;
    TriggerPanel *TriggerX;
    TriggerPanel *TriggerY;
    void OnPaint(wxPaintEvent &event);
    void OnSize(wxSizeEvent &event);
    void OnKeyPress(wxKeyEvent &event);
    void OnChangeType(wxCommandEvent &event);

    enum EVENT {
        TYPE_CHANGE = 5000
    };
};

#endif //__AXISDISPLAYPANEL__