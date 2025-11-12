#ifndef __MAINWINDOW__
#define __MAINWINDOW__

#include <wx/wx.h>
#include <wx/sizer.h>
#include "CardPanel.hpp"
#include "InfoWindow.hpp"
#include <filesystem>
#include <list>
#include "Controllers/Configuration.hpp"
#include "Views/TerminalPanel.hpp"

class MainWindow : public wxFrame {
   public:
    Configuration config;
    wxScrolledWindow* lwindow;
    InfoWindow* iwindow;
    TerminalPanel *twindow;
    wxBoxSizer* breadcrumbs;
    wxBitmapButton* forward;
    wxBitmapButton* backward;

    int selected_folders;
    int selected_files;
    CardPanel* selected_card;

    std::filesystem::path current;
    std::list<CardPanel*> folder_cards;
    std::list<CardPanel*> file_cards;
    std::list<std::string> forward_paths;

    MainWindow();

    void ChangePath(std::filesystem::path path);
    void ExecuteMenuEvent(int eventId);
    void OnFolderMenuClick(wxCommandEvent& event);

   private:
    wxScrolledWindow* CreateListingPanel();
    InfoWindow* CreateInfoPanel();
    wxBitmapButton* CreateBitmapButton(wxWindowID id, std::string name);
    wxBoxSizer* CreateSizer();
    wxButton* CreateBreadCrumbItem(wxString label, bool enabled = true);
    CardPanel* CreateCard(std::filesystem::directory_entry entry);

    void UpdatePathBreadCrumbs();
    void RefreshPath(bool reload = true);
    void RefreshStatusText();
    const wxSize CalcSize(int min_height, int width);

    void OnSizeLWindow(wxSizeEvent& event);
    void OnSizeIWindow(wxSizeEvent& event);
    void OnFolderRightClick(wxMouseEvent& event);
    void OnKeyPress(wxKeyEvent& event);
    void OnBreadCrumbClick(wxCommandEvent& event);
    void OnBackward(wxEvent& event);
    void OnForward(wxEvent& event);
};
#endif // __MAINWINDOW__