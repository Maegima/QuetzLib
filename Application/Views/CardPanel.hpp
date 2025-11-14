/**
 * @file CardPanel.hpp
 * @author André Lucas Maegima
 * @brief CardPanel class definition
 * @version 0.5
 * @date 2025-11-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _CARDPANEL_HPP_
#define _CARDPANEL_HPP_

#include <wx/wx.h>
#include <list>
#include "Controllers/Image.hpp"
#include "Controllers/FileInfo.hpp"

class MainWindow;

enum {
    RUNNER_MASK = 0x7FF,
    RUNNER_EVENT = 0x800,
    FIRST_EVENT = 0x1000
};

class CardPanel : public wxPanel {
   public:
    MainWindow* parent;
    FileInfo file;
    std::string name;
    Image* image;
    wxStaticText* label;
    bool m_mouseInside;
    bool selected;
    bool to_remove;

    CardPanel(MainWindow* parent, std::filesystem::directory_entry entry);
    ~CardPanel();

    void OnFolderLeftClick(wxMouseEvent& event);
    void OnFileLeftClick(wxMouseEvent& event);

    void OnEnterPanel(wxMouseEvent& event);
    void OnLeavePanel(wxMouseEvent& event);

    void OnRightClick(wxMouseEvent& event);
    void OnLeftClick(wxMouseEvent& event);
    void OnTextClick(wxMouseEvent& event);
    void SkipMouseEvent(wxMouseEvent &event);

    struct CompareCards {
        bool operator()(const CardPanel* c1, const CardPanel* c2) const;
    };

    typedef std::list<CardPanel *>::iterator CardIterator;

    void SelectItem(bool select, bool highlight = true);
   private:
    wxStaticText* CreateLabel(std::filesystem::directory_entry entry);
    Image* CreateImage(std::filesystem::directory_entry entry);
    std::pair<CardIterator, CardIterator> GetIterators(CardPanel* c1, CardPanel* c2);
};

#endif  // _CARDPANEL_HPP_