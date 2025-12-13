/**
 * @file CardCtrl.hpp
 * @author André Lucas Maegima
 * @brief CardCtrl class definition
 * @version 0.5
 * @date 2025-11-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __CARDCTRL__
#define __CARDCTRL__

#include <wx/wx.h>
#include <list>
#include "Controllers/Image.hpp"
#include "Controllers/FileInfo.hpp"

class MainWind;

enum { RUNNER_MASK = 0x7FF, RUNNER_EVENT = 0x800, FIRST_EVENT = 0x1000 };

class CardCtrl : public wxPanel {
  public:
    MainWind *parent;
    FileInfo file;
    std::string name;
    Image *image;
    wxStaticText *label;
    bool m_mouseInside;
    bool selected;
    bool to_remove;

    CardCtrl(MainWind *parent, std::filesystem::directory_entry entry);
    ~CardCtrl();

    void OnFolderLeftClick(wxMouseEvent &event);
    void OnFileLeftClick(wxMouseEvent &event);

    void OnEnterPanel(wxMouseEvent &event);
    void OnLeavePanel(wxMouseEvent &event);

    void OnRightClick(wxMouseEvent &event);
    void OnLeftClick(wxMouseEvent &event);
    void OnTextClick(wxMouseEvent &event);
    void SkipMouseEvent(wxMouseEvent &event);

    struct CompareCards {
        bool operator()(const CardCtrl *c1, const CardCtrl *c2) const;
    };

    typedef std::list<CardCtrl *>::iterator CardIterator;

    void SelectItem(bool select, bool highlight = true);

  private:
    wxStaticText *CreateLabel(std::filesystem::directory_entry entry);
    Image *CreateImage(std::filesystem::directory_entry entry);
    std::pair<CardIterator, CardIterator> GetIterators(CardCtrl *c1, CardCtrl *c2);
};

#endif // __CARDCTRL__