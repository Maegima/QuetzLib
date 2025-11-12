#include "TerminalPanel.hpp"

TerminalPanel::TerminalPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
: wxTextCtrl(parent, id, wxEmptyString, pos, size, wxTE_MULTILINE) {
    SetEditable(false);
    SetBackgroundColour(bg_color);
    out_style = wxTextAttr(out_color);
    out_style.SetFont(font);
    SetDefaultStyle(out_style);
    err_style = wxTextAttr(err_color);
    err_style.SetFont(font);
}

void TerminalPanel::WriteToTerminal(std::stringstream &stream, const wxTextAttr &style) {
    std::string line;
    SetDefaultStyle(style);
    while (getline(stream, line))
        AppendText("> " + line + "\n");
    stream.clear();
}

void TerminalPanel::WriteBuffered(std::stringstream &stream, const wxTextAttr &style, const std::string &text) {
    size_t iend = text.find_last_of('\n');
    if (iend == std::string::npos) {
        stream << text;
        return;
    }
    stream << text.substr(0, iend);
    WriteToTerminal(stream, style);
    stream << text.substr(iend + 1, text.length() - iend);
}

void TerminalPanel::WriteOut(const std::string &text) {
    WriteBuffered(out_stream, out_style, text);
}

void TerminalPanel::WriteErr(const std::string &text) {
    WriteBuffered(err_stream, err_style, text);
}

void TerminalPanel::Flush() {
    WriteToTerminal(out_stream, out_style);
    WriteToTerminal(err_stream, err_style);
}
