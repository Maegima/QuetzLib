/**
 * @file Application.hpp
 * @author André Lucas Maegima
 * @brief Disklist Application definitions
 * @version 0.4
 * @date 2025-11-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef DISKLIST_APPLICATION_HPP
#define DISKLIST_APPLICATION_HPP

#include <wx/wx.h>

class Application : public wxApp {
   public:
    virtual bool OnInit();
};

#endif /* DISKLIST_APPLICATION_HPP */
