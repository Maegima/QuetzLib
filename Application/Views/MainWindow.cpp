/**
 * @file MainWindow.cpp
 * @author André Lucas Maegima
 * @brief Listing window implementation
 * @version 0.4
 * @date 2025-11-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "wx/wrapsizer.h"
#include "MainWindow.hpp"

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Files", wxDefaultPosition, wxSize(1200, 600)),
    config(".conf"),
    lwindow(CreateListingPanel()),
    iwindow(new InfoWindow(this, wxID_ANY, wxPoint(800, 0), wxSize(250, 600))),
    breadcrumbs(new wxBoxSizer(wxHORIZONTAL)),
    forward(CreateBitmapButton(wxID_FORWARD, "forward")),
    backward(CreateBitmapButton(wxID_BACKWARD, "backward")),
    selected_folders(0),
    selected_files(0),
    selected_card(nullptr) {
    forward->Bind(wxEVT_BUTTON, &MainWindow::OnForward, this);
    backward->Bind(wxEVT_BUTTON, &MainWindow::OnBackward, this);

    SetSizer(CreateSizer());
    CreateStatusBar();

    ChangePath(config.config["root"]);
}

wxScrolledWindow *MainWindow::CreateListingPanel() {
    wxScrolledWindow *window = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER);
    window->SetBackgroundColour(*wxWHITE);
    window->Bind(wxEVT_SIZE, &MainWindow::OnSize, this, wxID_ANY);
    window->Bind(wxEVT_RIGHT_DOWN, &MainWindow::OnFolderRightClick, this, wxID_ANY);
    window->Bind(wxEVT_CHAR_HOOK, &MainWindow::OnKeyPress, this, wxID_ANY);

     window->Bind(wxEVT_AUX1_DOWN, &MainWindow::OnBackward, this);
     window->Bind(wxEVT_AUX2_DOWN, &MainWindow::OnForward, this);

    wxWrapSizer *sizer = new wxWrapSizer(wxHORIZONTAL);
    window->SetSizer(sizer);

    window->SetScrollbars(0, 40, 0, sizer->GetSize().GetHeight() / 40);
    return window;
}

wxBitmapButton *MainWindow::CreateBitmapButton(wxWindowID id, std::string name) {
    wxImage image = config.image[name]->Scale(38, 38, wxIMAGE_QUALITY_HIGH);
    wxImage image_hover = image.Copy();
    image_hover.ChangeHSV(1, 1, -0.25);
    wxBitmapButton *btn = new wxBitmapButton(this, id, image, wxDefaultPosition, wxSize(32, 32), wxBORDER_NONE);
    btn->SetBitmapHover(image_hover);
    return btn;
}

wxBoxSizer *MainWindow::CreateSizer() {
    wxBoxSizer *toolbarSizer = new wxBoxSizer(wxHORIZONTAL);
    toolbarSizer->AddSpacer(3);
    toolbarSizer->Add(backward, 0, wxALL);
    toolbarSizer->AddSpacer(1);
    toolbarSizer->Add(forward, 0, wxALL);
    toolbarSizer->AddSpacer(3);
    toolbarSizer->Add(breadcrumbs, 1, wxEXPAND);
    toolbarSizer->AddSpacer(3);

    wxBoxSizer *windowSizer = new wxBoxSizer(wxHORIZONTAL);
    windowSizer->Add(lwindow, wxEXPAND);
    windowSizer->Add(iwindow);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(toolbarSizer, 0, wxEXPAND);
    sizer->Add(windowSizer, 1, wxEXPAND);
    return sizer;
}

void MainWindow::ChangePath(std::filesystem::path path) {
    std::error_code errorcode;
     if (this->current != path && std::filesystem::is_directory(path, errorcode)) {
        this->current = path;
        backward->Enable(current != config.config["root"]);
        forward->Enable(forward_paths.size() > 0);
        UpdatePathBreadCrumbs();
        RefreshPath();
     }
}

void MainWindow::UpdatePathBreadCrumbs() {
    size_t rootlength = config.config["root"].length();
    std::string display = this->current.string().length() <= rootlength ? "" : this->current.string().substr(rootlength + 1);
    wxArrayString folders = wxSplit(wxString::FromUTF8(display), '/');
    breadcrumbs->Clear(true);
    std::filesystem::path path = config.config["root"];
    for (const auto& folder : folders) {
        path /= folder.ToUTF8().data();
        breadcrumbs->Add(CreateBreadCrumbItem("<tt><b>&gt;</b></tt>", false), 0, wxEXPAND | wxALL, 1);
        auto item = CreateBreadCrumbItem(folder);
        item->SetName(wxString::FromUTF8(path.string()));
        item->Bind(wxEVT_BUTTON, &MainWindow::OnBreadCrumbClick, this);
        breadcrumbs->Add(item, 0, wxEXPAND | wxALL, 1);
    }
    if (folders.empty()) {
        breadcrumbs->Add(CreateBreadCrumbItem("<tt><b>&gt;</b></tt>", false), 0, wxEXPAND | wxALL, 1);
    }
}

wxButton* MainWindow::CreateBreadCrumbItem(wxString label, bool enabled) {
    auto item = new wxButton(this, wxID_ANY, label, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE | wxBU_EXACTFIT);
    item->SetLabelMarkup(label);
    item->Enable(enabled);
    return item;
}

void MainWindow::RefreshPath(bool reload) {
    auto* sizer = lwindow->GetSizer();
    sizer->Clear(reload);
    this->selected_files = 0;
    this->selected_folders = 0;
    lwindow->SetFocus();
    if (reload) {
        this->file_cards.clear();
        this->folder_cards.clear();
        for (auto const& entry : std::filesystem::directory_iterator{current}) {
            auto card = CreateCard(entry);
            if(entry.is_directory()) {
                folder_cards.push_back(card);
            } else {
                file_cards.push_back(card);
            }
        }
        this->file_cards.sort(CardPanel::CompareCards());
        this->folder_cards.sort(CardPanel::CompareCards());
    } else {
        auto remove_cards = [](CardPanel* card) {
            bool result = card->to_remove;
            if (result) delete card;
            return result;
        };
        std::erase_if(file_cards, remove_cards);
        std::erase_if(folder_cards, remove_cards);
    }
    for (auto const& card : folder_cards) {
        sizer->Add(card, 0, wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 0);
    }
    for (auto const& card : file_cards) {
        sizer->Add(card, 0, wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 0);
    }
    if (reload) {
        lwindow->SetScrollbars(0, 40, 0, sizer->GetSize().GetHeight() / 40);
    }
    RefreshStatusText();
    this->SendSizeEvent();
    lwindow->Refresh();
}

 void MainWindow::RefreshStatusText() {
     std::string text = std::to_string(folder_cards.size()) + " Folders, " + std::to_string(file_cards.size()) + " Files";
     SetStatusText(wxString::FromUTF8(text));
 }

void MainWindow::ExecuteMenuEvent(int eventId) {
    bool refresh = false;
    wxDirDialog* lsw = nullptr;
    std::filesystem::path path = "";
    std::filesystem::path root = this->config.config["root"];
    std::cout << "MenuEvent:" << eventId << std::endl;
}

CardPanel* MainWindow::CreateCard(std::filesystem::directory_entry entry) {
    auto card = new CardPanel(this, entry);
    card->Bind(wxEVT_RIGHT_DOWN, &MainWindow::OnFolderRightClick, this, wxID_ANY);
    return card;
}

void MainWindow::OnSize(wxSizeEvent& event) {
    int width = lwindow->m_width;
    int items = width / 200;
    int spacing = items ? (width % 200) / items : 0;
    auto sizer = lwindow->GetSizer();
    for (auto& item : sizer->GetChildren()) {
        item->SetBorder(spacing / 2);
    }
    auto newSize = this->GetClientSize();
    lwindow->SetSize(newSize.x - 250, newSize.y);
    Refresh();
    event.Skip();
}

void MainWindow::OnBackward(wxEvent& event) {
    if (current != this->config.config["root"]) {
        forward_paths.push_front(current);
        ChangePath(current.parent_path());
    }
}

void MainWindow::OnForward(wxEvent& event) {
    if (forward_paths.size() > 0) {
        std::string path = forward_paths.front();
        forward_paths.pop_front();
        ChangePath(path);
    }
}

void MainWindow::OnBreadCrumbClick(wxCommandEvent& event) {
    wxButton* breadcrumb = (wxButton*)event.GetEventObject();
    ChangePath(breadcrumb->GetName().ToUTF8().data());
}

void MainWindow::OnFolderMenuClick(wxCommandEvent& evt) {
    switch (evt.GetId()) {
        case NOOP:
            break;
    }
}

void MainWindow::OnKeyPress(wxKeyEvent& event) {
    int uc = event.GetKeyCode();
    // int event_first = 2001;
    if (event.ControlDown()) {
        switch (uc) {
            // case '1' ... '9':
            //     ExecuteMenuEvent(event_first + uc - '1');
            //     break;
            case 'A':
                for (auto const& card : file_cards) {
                    card->SelectItem(true);
                }
                break;
        }
    } else if (event.AltDown()) {
        switch (uc) {
            case WXK_LEFT:
                OnBackward(event);
                break;
            case WXK_RIGHT:
                OnForward(event);
                break;
        }
    }
    // if (uc >= WXK_F6 && uc <= WXK_F8) {
    //     ExecuteMenuEvent(MOVE_TO_FOLDER + 1 + uc - WXK_F6);
    // }
    event.Skip();
}

void MainWindow::OnFolderRightClick(wxMouseEvent& evt) {
    wxMenu menu;
    menu.Append(NOOP, "Noop...");
    menu.Connect(wxEVT_MENU, wxCommandEventHandler(MainWindow::OnFolderMenuClick), nullptr, this);
    PopupMenu(&menu);
}
