/**
 * @file AxisDisplaySect.hpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __AXISDISPLAYSECT__
#define __AXISDISPLAYSECT__

#include "Views/Control/TriggerCtrl.hpp"
#include "Views/Control/StickCtrl.hpp"

class AxisDisplaySect : public wxPanel {
  public:
    AxisDisplaySect(wxWindow *parent, int axes, int x_axis = 0, int y_axis = 1);
    void UpdatePosition(int x, int y);
    wxChoice *fst_axis;
    wxChoice *snd_axis;
    wxChoice *sel_type;

  private:
    StickCtrl *Stick;
    TriggerCtrl *TriggerX;
    TriggerCtrl *TriggerY;
    void OnChangeType(wxCommandEvent &event);

    enum EVENT {
        TYPE_CHANGE = 5000
    };
};

#endif //__AXISDISPLAYSECT__