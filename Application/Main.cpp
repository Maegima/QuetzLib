/**
 * @file Main.cpp
 * @author André Lucas Maegima
 * @brief Folder listing program and ROM launcher.
 * @version 0.4
 * @date 2025-11-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Main.hpp"

// wxIMPLEMENT_APP(MyApp);

inline wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction) new Application);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        wxImage::AddHandler(new wxPNGHandler());
        wxImage::AddHandler(new wxJPEGHandler());
        return wxEntry(argc, argv);
    }
}