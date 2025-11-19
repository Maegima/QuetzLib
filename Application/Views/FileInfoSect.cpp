/**
 * @file FileInfoSect.cpp
 * @author André Lucas Maegima
 * @brief Information Window class implementation
 * @version 0.5
 * @date 2025-11-12
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "FileInfoSect.hpp"
#include <wx/hyperlink.h>

FileInfoSect::FileInfoSect(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, wxID_ANY, pos, size, wxBORDER_SUNKEN) {
    SetBackgroundColour(*wxWHITE);
    SetSizer(new wxBoxSizer(wxVERTICAL));
}

void FileInfoSect::FillGrid(std::list<std::pair<wxString, wxString>> lines) {
    auto sizer = this->GetSizer();
    sizer->Clear(true);
    for (auto const& pair : lines) {
        wxBoxSizer* line = new wxBoxSizer(wxHORIZONTAL);
        line->Add(CreateCenteredText(pair.first, wxSize(60, 24)), 0, wxEXPAND | wxTOP | wxRIGHT, 4);
        line->Add(CreateCenteredText(pair.second), 1, wxEXPAND | wxTOP | wxRIGHT, 4);
        sizer->Add(line, 0, wxEXPAND | wxLEFT, 4);
    }
    this->SendSizeEvent();
    this->Refresh();
}

wxPanel* FileInfoSect::CreateCenteredText(wxString label, wxSize size) {
    wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, size);
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    wxControl *text = nullptr;
    if(label.StartsWith("https:") || label.StartsWith("http:")) {
        text = new wxHyperlinkCtrl(panel, wxID_ANY, label, label);
    } else {
        text = new wxStaticText(panel, wxID_ANY, label);
    }
    int max_text_size = 230;
    while (text->GetBestWidth(text->m_height) > 230 && max_text_size > 0) {
        int parts = text->GetBestWidth(text->m_height) / max_text_size;
        int size = label.length() / (parts + 1);
        wxString newstr = "";
        for (int i = 0; i < parts; i++) {
            newstr += label.substr(i * size, size) + "\n";
        }
        newstr += label.substr(parts * size);
        text->SetLabel(newstr);
        max_text_size -= 10;
    }
    text->SetFont(wxFont(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    panel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    sizer->Add(text, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2);
    panel->SetSizer(sizer);
    return panel;
}