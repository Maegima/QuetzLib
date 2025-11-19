#ifndef __MAINWIND__
#define __MAINWIND__

#include <wx/wx.h>
#include <wx/sizer.h>
#include "CardCtrl.hpp"
#include "FileInfoSect.hpp"
#include <filesystem>
#include <list>
#include "Controllers/Configuration.hpp"
#include "Views/TerminalSect.hpp"

class MainWind : public wxFrame {
   public:
    Configuration config;
    wxScrolledWindow* lwindow;
    FileInfoSect* iwindow;
    TerminalSect *twindow;
    wxBoxSizer* breadcrumbs;
    wxBitmapButton* forward;
    wxBitmapButton* backward;

    int selected_folders;
    int selected_files;
    CardCtrl* selected_card;

    std::filesystem::path current;
    std::list<CardCtrl*> folder_cards;
    std::list<CardCtrl*> file_cards;
    std::list<std::string> forward_paths;

    MainWind();

    void ChangePath(std::filesystem::path path);
    void ExecuteMenuEvent(int eventId);
    void OnFolderMenuClick(wxCommandEvent& event);

   private:
    wxScrolledWindow* CreateListingPanel();
    FileInfoSect* CreateInfoPanel();
    wxBitmapButton* CreateBitmapButton(wxWindowID id, std::string name);
    wxBoxSizer* CreateSizer();
    wxButton* CreateBreadCrumbItem(wxString label, bool enabled = true);
    CardCtrl* CreateCard(std::filesystem::directory_entry entry);

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
#endif // __MAINWIND__