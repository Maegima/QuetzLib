/**
 * @file StickCtrl.hpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __STICKCTRL__
#define __STICKCTRL__

#include "Views/Control/AxisCtrl.hpp"

class StickCtrl : public AxisCtrl {
  public:
    StickCtrl(wxWindow *parent);
    void UpdatePosition(int16_t x, int16_t y);

  private:
    void Draw(wxDC &dc);
};

#endif // __STICKCTRL__