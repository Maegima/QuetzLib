/**
 * @file Application.cpp
 * @author André Lucas Maegima
 * @brief Disklist Application override implementations
 * @version 0.4
 * @date 2025-11-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Application.hpp"
#include "Views/MainWindow.hpp"

bool Application::OnInit() {
    wxLog::SetActiveTarget(new wxLogStderr());
    MainWindow* window = new MainWindow();
    window->Show(true);
    return true;
}