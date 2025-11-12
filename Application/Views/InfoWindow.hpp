
/*
 * @file InfoWindow.hpp
 * @author André Lucas Maegima
 * @brief Information Window class definition
 * @version 0.5
 * @date 2025-11-12
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _INFOWINDOW_HPP_
#define _INFOWINDOW_HPP_

#include <wx/wx.h>
#include <list>

class InfoWindow : public wxPanel {
   public:
    InfoWindow(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);

    void FillGrid(std::list<std::pair<wxString, wxString>> lines);
   private:
    wxPanel* CreateCenteredText(wxString label, wxSize size = wxDefaultSize);
};

#endif  // _INFOWINDOW_HPP_