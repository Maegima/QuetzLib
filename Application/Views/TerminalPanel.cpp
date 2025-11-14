#include "TerminalPanel.hpp"
#include "Controllers/Process.hpp"
#include <sys/poll.h>
#include <sys/wait.h>

TerminalPanel::TerminalPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
: wxTextCtrl(parent, id, wxEmptyString, pos, size, wxTE_MULTILINE) {
    SetEditable(false);
    SetBackgroundColour(bg_color);
    out_style = wxTextAttr(out_color);
    out_style.SetFont(font);
    SetDefaultStyle(out_style);
    err_style = wxTextAttr(err_color);
    err_style.SetFont(font);
    Bind(wxEVT_THREAD, &TerminalPanel::WriteErr, this, Process::WRITE_ERR);
    Bind(wxEVT_THREAD, &TerminalPanel::WriteOut, this, Process::WRITE_OUT);
    Bind(wxEVT_THREAD, &TerminalPanel::FlushTrm, this, Process::FLUSH_TRM);
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

void TerminalPanel::WriteOut(wxThreadEvent &event) {
    WriteBuffered(out_stream, out_style, event.GetString().utf8_string());
}

void TerminalPanel::WriteErr(wxThreadEvent &event) {
    WriteBuffered(err_stream, err_style, event.GetString().utf8_string());
}

void TerminalPanel::FlushTrm(wxThreadEvent &event) {
    WriteToTerminal(out_stream, out_style);
    WriteToTerminal(err_stream, err_style);
}

void TerminalPanel::RunCommand(const std::string &command, const std::vector<std::string> &args) {
    Process(this).Execute(command, args);
}