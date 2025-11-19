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
#include "Views/Window/MainWind.hpp"

bool Application::OnInit() {
    wxLog::SetActiveTarget(new wxLogStderr());
    MainWind* window = new MainWind();
    window->Show(true);
    return true;
}