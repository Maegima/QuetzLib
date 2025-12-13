/**
 * @file Process.hpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-13
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __PROCESS__
#define __PROCESS__

#include <wx/wx.h>
#include <string>
#include <vector>

class Process {
  private:
    int RunCommand(const std::string &cmd, const std::vector<std::string> &args);
    int PollCommand();
    static void Loop(wxWindow *term, int pid, int outfd, int errfd);
    static void SendEvent(wxWindow *wind, const std::string &msg, int select);
    wxWindow *term;
    int pid = -1;
    int outfd[2];
    int errfd[2];

  public:
    Process(wxWindow *term);
    int Execute(const std::string &cmd, const std::vector<std::string> &args = {});
    enum EVENT { WRITE = 3000, WRITE_OUT = 3000, WRITE_ERR = 3001, FLUSH_TRM = 3002 };

}; // namespace Process

#endif // __PROCESS__