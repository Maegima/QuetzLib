/**
 * @file TriggerCtrl.hpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __TRIGGERCTRL__
#define __TRIGGERCTRL__

#include "Views/Control/AxisCtrl.hpp"
#include <cstdint>

class TriggerCtrl : public AxisCtrl {
  public:
    TriggerCtrl(wxWindow *parent, bool bidirectional);
    void SetValue(uint16_t val) { SetX(val); }

  private:
    static const int16_t min_value = INT16_MIN;
    static const int16_t max_value = INT16_MAX;
    int dead_zone = (max_value - min_value)/8;
    bool bidirectional;

    void Draw(wxDC &dc);
    void DrawDeadZone(wxDC &dc, int progressX, int width, int height);
};

#endif // __TRIGGERCTRL__