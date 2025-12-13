/**
 * @file HatsCtrl.hpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __HATSCTRL__
#define __HATSCTRL__

#include <cstdint>
#include <wx/wx.h>
#include <wx/tglbtn.h>

class HatsCtrl : public wxPanel {
  private:
    wxWindow *parent;
    wxToggleButton *hats[4];

  public:
    HatsCtrl(wxWindow *parent);
    void SetValue(uint8_t val);
};
#endif // __HATSCTRL__
