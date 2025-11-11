/**
 * @file Process.hpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __PROCESS__
#define __PROCESS__

#include <string>
#include <vector>

namespace Process {
void set_outputs(int outfd[2], int errfd[2]);
int command(const std::string &cmd, const std::vector<std::string> &args, int outfd[2], int errfd[2]);
int wait_command(int pid, int outfd[2], int errfd[2]);
int execute(const std::string &cmd, const std::vector<std::string> &args = {});
}; // namespace Process

#endif // __PROCESS__