
/**
 * @file TerminalPanel.hpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __TERMINALPANEL__
#define __TERMINALPANEL__

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <sstream>

class TerminalPanel : public wxTextCtrl {
  private:
    const wxColour bg_color = wxColour(17, 15, 40);
    const wxColour err_color = wxColour(250, 130, 50);
    const wxColour out_color = wxColour(34, 119, 255);
    const wxFont font = wxFontInfo(11).FaceName("Hack Nerd Font Mono").Bold(true);
    wxTextAttr err_style;
    wxTextAttr out_style;
    std::stringstream err_stream;
    std::stringstream out_stream;
    void WriteToTerminal(std::stringstream &stream, const wxTextAttr &style);
    void WriteBuffered(std::stringstream &stream, const wxTextAttr &style, const std::string &text);

  public:
    TerminalPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);
    void WriteOut(const std::string &text);
    void WriteErr(const std::string &text);
    void Flush();
};

#endif // __TERMINALPANEL__