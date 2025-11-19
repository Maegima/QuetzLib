/**
 * @file CardCtrl.cpp
 * @author André Lucas Maegima
 * @brief CardCtrl class implementation
 * @version 0.5
 * @date 2025-11-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "CardCtrl.hpp"
#include "Views/Window/MainWind.hpp"
#include <wx/utils.h>
#include <ranges>

CardCtrl::CardCtrl(MainWind *parent, std::filesystem::directory_entry entry)
: wxPanel(parent->lwindow, wxID_ANY),
  parent(parent),
  file(FileInfo(entry, false)),
  name(entry.path().filename().string()),
  image(CreateImage(entry)),
  label(CreateLabel(entry)),
  m_mouseInside(false),
  selected(false),
  to_remove(false) {
    auto sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizer);
    sizer->AddSpacer(5);
    sizer->Add(image, 0);
    sizer->Add(label, 0, wxALIGN_CENTER);
    sizer->AddSpacer(10);
    std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
    Bind(wxEVT_ENTER_WINDOW, &CardCtrl::OnEnterPanel, this);
    Bind(wxEVT_LEAVE_WINDOW, &CardCtrl::OnLeavePanel, this);
    Bind(wxEVT_AUX1_DOWN, &CardCtrl::SkipMouseEvent, this);
    Bind(wxEVT_AUX2_DOWN, &CardCtrl::SkipMouseEvent, this);
}

CardCtrl::~CardCtrl() {
    delete image;
    delete label;
}

wxStaticText *CardCtrl::CreateLabel(std::filesystem::directory_entry entry) {
    wxString name = wxString::FromUTF8(entry.path().filename());
    wxStaticText *text = new wxStaticText(this, wxID_ANY, name, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    int max_text_size = 180;
    while (text->m_width > 200) {
        int parts = text->m_width / max_text_size;
        int size = name.length() / (parts + 1);
        wxString newstr = "";
        for (int i = 0; i < parts; i++) {
            newstr += name.substr(i * size, size) + "\n";
        }
        newstr += name.substr(parts * size);
        text->SetLabel(newstr);
        max_text_size -= 10;
    }
    if (entry.is_directory()) {
        text->Bind(wxEVT_LEFT_DCLICK, &CardCtrl::OnFolderLeftClick, this, wxID_ANY);
    } else {
        text->Bind(wxEVT_LEFT_DOWN, &CardCtrl::OnFileLeftClick, this, wxID_ANY);
    }
    text->Bind(wxEVT_LEFT_DOWN, &CardCtrl::OnTextClick, this, wxID_ANY);
    text->Bind(wxEVT_RIGHT_DOWN, &CardCtrl::OnRightClick, this, wxID_ANY);
    text->Bind(wxEVT_AUX1_DOWN, &CardCtrl::SkipMouseEvent, this);
    text->Bind(wxEVT_AUX2_DOWN, &CardCtrl::SkipMouseEvent, this);
    return text;
}

Image *CardCtrl::CreateImage(std::filesystem::directory_entry entry) {
    std::vector<std::string> img_exts = parent->config.image_extension;
    std::string extension = entry.path().extension().string();
    Image *img = new Image(this, entry, parent->config);
    if (entry.is_directory()) {
        img->Bind(wxEVT_LEFT_DCLICK, &CardCtrl::OnFolderLeftClick, this, wxID_ANY);
    } else {
        img->Bind(wxEVT_LEFT_DOWN, &CardCtrl::OnFileLeftClick, this, wxID_ANY);
    }
    img->Bind(wxEVT_LEFT_DOWN, &CardCtrl::OnLeftClick, this, wxID_ANY);
    img->Bind(wxEVT_RIGHT_DOWN, &CardCtrl::OnRightClick, this, wxID_ANY);
    img->Bind(wxEVT_AUX1_DOWN, &CardCtrl::SkipMouseEvent, this);
    img->Bind(wxEVT_AUX2_DOWN, &CardCtrl::SkipMouseEvent, this);
    return img;
}

std::pair<CardCtrl::CardIterator, CardCtrl::CardIterator> CardCtrl::GetIterators(CardCtrl *c1, CardCtrl *c2) {
    CardIterator it = this->parent->file_cards.begin();
    CardIterator first = this->parent->file_cards.end();
    CardIterator second = this->parent->file_cards.end();
    while (it != this->parent->file_cards.end() && first == this->parent->file_cards.end()) {
        CardCtrl *card = *(it++);
        if (card == c1 || card == c2) first = it;
    }
    while (it != this->parent->file_cards.end() && second == this->parent->file_cards.end()) {
        CardCtrl *card = *(it++);
        if (card == c1 || card == c2) second = it;
    }
    return {first, second};
}

void CardCtrl::OnLeftClick(wxMouseEvent &event) {
    SetFocus();
    if (wxGetKeyState(WXK_CONTROL)) {
        SelectItem(!this->selected);
    } else if (wxGetKeyState(WXK_SHIFT)) {
        CardCtrl *last_card = this->parent->selected_card;
        if (last_card != nullptr) {
            auto [begin, end] = GetIterators(last_card, this);
            for (auto it = begin; it != end; it++) {
                (*it)->SelectItem(true);
            }
        }
        SelectItem(true);
    } else {
        std::vector<std::list<CardCtrl *>> cards = {parent->folder_cards, parent->file_cards};
        for (auto const &card : std::ranges::join_view(cards)) {
            card->SelectItem(false, false);
        }
        SelectItem(true);
    }
    this->parent->selected_card = this;
    event.Skip();
}

void CardCtrl::SelectItem(bool select, bool highlight) {
    if (this->selected == select) {
        return;
    }
    this->selected = select;
    if (this->selected) {
        this->image->ChangeLightness(130);
        this->label->SetBackgroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_GRAYTEXT));
        this->label->SetForegroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_HIGHLIGHTTEXT));
    } else if (highlight) {
        this->image->ChangeLightness(130);
        this->label->SetBackgroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_HIGHLIGHT));
        this->label->SetForegroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_HIGHLIGHTTEXT));
    } else {
        this->image->ChangeLightness(100);
        this->label->SetBackgroundColour(*wxWHITE);
        this->label->SetForegroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_BTNTEXT));
    }
    if (this->file.type == FileType::Directory) {
        this->parent->selected_folders += this->selected ? 1 : -1;
    } else {
        this->parent->selected_files += this->selected ? 1 : -1;
    }
}

void CardCtrl::OnTextClick(wxMouseEvent &event) {
    event.Skip();
}

void CardCtrl::SkipMouseEvent(wxMouseEvent &event) {
    wxQueueEvent(GetParent()->GetEventHandler(), new wxMouseEvent(event.GetEventType()));
}

void CardCtrl::OnFolderLeftClick(wxMouseEvent &event) {
    parent->forward_paths.clear();
    parent->ChangePath(file.path);
}

void CardCtrl::OnFileLeftClick(wxMouseEvent &event) {
    std::list<std::pair<wxString, wxString>> list;
    for (const auto &[key, expression] : parent->config.file_info) {
        std::string value = file.get_value(expression);
        if (value != "<null>") {
            list.push_back({key, wxString::FromUTF8(value)});
        }
    }
    parent->iwindow->FillGrid(list);
}

bool CardCtrl::CompareCards::operator()(const CardCtrl *c1, const CardCtrl *c2) const {
    if (c1->file.type != c2->file.type)
        return c1->file.type == FileType::Directory;
    return c1->name < c2->name;
}

void CardCtrl::OnRightClick(wxMouseEvent &evt) {
    this->OnLeftClick(evt);
    wxMenu menu;
    for(uint i = 0; i < parent->config.runners.size(); i++) {
        menu.Append(RUNNER_EVENT + i, parent->config.runners[i].first);
    }
    menu.Connect(wxEVT_MENU, wxCommandEventHandler(MainWind::OnFolderMenuClick), nullptr, this->parent);
    PopupMenu(&menu);
}

bool CheckPosition(wxRect rect, wxPoint pos, int box) {
    return rect.GetX() <= pos.x - box && rect.GetRight() >= pos.x + box && rect.GetY() <= pos.y - box && rect.GetBottom() >= pos.y + box;
}

void CardCtrl::OnEnterPanel(wxMouseEvent &event) {
    this->image->ChangeLightness(150);
    this->label->SetBackgroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_HIGHLIGHT));
    this->label->SetForegroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_HIGHLIGHTTEXT));
    if (selected) {
        this->label->SetBackgroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_GRAYTEXT));
        this->label->SetForegroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_HIGHLIGHTTEXT));
    }
}

void CardCtrl::OnLeavePanel(wxMouseEvent &event) {
    auto mousePosition = ClientToScreen(event.GetPosition());
    auto rect = GetScreenRect();
    if (CheckPosition(rect, mousePosition, 0)) {
        this->image->ChangeLightness(150);
        this->label->SetBackgroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_HIGHLIGHT));
        this->label->SetForegroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_HIGHLIGHTTEXT));
    } else {
        if (selected)
            this->image->ChangeLightness(130);
        else
            this->image->ChangeLightness(100);
        this->label->SetBackgroundColour(*wxWHITE);
        this->label->SetForegroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_BTNTEXT));
    }
    if (selected) {
        this->label->SetBackgroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_GRAYTEXT));
        this->label->SetForegroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_HIGHLIGHTTEXT));
    }
}
