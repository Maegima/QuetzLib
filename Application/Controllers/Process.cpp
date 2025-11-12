/**
 * @file Process.cpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "Process.hpp"
#include <sstream>
#include <sys/poll.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

namespace Process {
void set_outputs(int outfd[2], int errfd[2]) {
    close(outfd[0]);
    close(errfd[0]);
    dup2(outfd[1], 1);
    dup2(errfd[1], 2);
    close(outfd[1]);
    close(errfd[1]);
}

int command(const std::string &cmd, const std::vector<std::string> &args, int outfd[2], int errfd[2]) {
    set_outputs(outfd, errfd);
    std::vector<const char*> c_args;
    c_args.reserve(args.size() + 1);
    for(const std::string & str : args) {
        c_args.push_back(str.c_str());
    }
    c_args.push_back(nullptr);
    int result = execvp(cmd.c_str(), (char *const*) c_args.data());
    return result;
}

int wait_command(int pid, int outfd[2], int errfd[2], TerminalPanel *term) {
    char *buff = new char[1024];
    close(outfd[1]);
    close(errfd[1]);
    pollfd fds[2];
    fds[0].fd = outfd[0];
    fds[1].fd = errfd[0];
    fds[0].events = POLLIN;
    fds[1].events = POLLIN;
    int desc_n = 2;
    int ret = poll(fds, 2, 500);
    while(ret > -1 && desc_n > 0) {
        for(int i = 0; i < 2; i++) {
            if(fds[i].revents & POLLIN) {
                int n = read(fds[i].fd, buff, 1023);
                if(n > 0) {
                    buff[n] = 0;
                    if(i) term->WriteErr(buff);
                    else term->WriteOut(buff);
                }
            } else if(fds[i].revents & POLLHUP) {
                close(fds[i].fd);
                fds[i].fd = -1;
                desc_n--;
            } else {
                if(fds[i].revents != 0){
                    std::stringstream ss;
                    ss << "fd: " << i << " event: %d\n";
                    term->WriteErr(ss.str());
                }
            }
        }
        ret = poll(fds, 2, 500);
    }
    int status = 0;
    int result = waitpid(pid, &status, 0);
    term->Flush();
    close(outfd[0]);
    close(errfd[0]);
    return 0;
}

int execute(const std::string &cmd, const std::vector<std::string> &args, TerminalPanel *term) {
    int outfd[2], errfd[2];
    pipe(outfd);
    pipe(errfd);
    int pid = fork();
    if(pid == 0) exit(command(cmd, args, outfd, errfd));
    if(pid > 0) return wait_command(pid, outfd, errfd, term);
    return -1;
}
} // namespace Execute
