/**
 * @file Process.cpp
 * @author André Lucas Maegima
 * @brief
 * @version 0.5
 * @date 2025-11-13
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "Process.hpp"
#include <sstream>
#include <sys/poll.h>
#include <sys/wait.h>
#include <unistd.h>
#include <thread>

Process::Process(wxWindow *term) : term(term) {
    pipe(outfd);
    pipe(errfd);
}

int Process::RunCommand(const std::string &cmd, const std::vector<std::string> &args) {
    close(outfd[0]);
    close(errfd[0]);
    dup2(outfd[1], 1);
    dup2(errfd[1], 2);
    close(outfd[1]);
    close(errfd[1]);
    std::vector<const char*> c_args;
    c_args.reserve(args.size() + 1);
    for(const std::string & str : args) {
        c_args.push_back(str.c_str());
    }
    c_args.push_back(nullptr);
    int result = execvp(cmd.c_str(), (char *const*) c_args.data());
    return result;
}

int Process::PollCommand() {
    close(outfd[1]);
    close(errfd[1]);
    int result = 0;
    try {
        std::thread(Process::Loop, term, pid, outfd[0], errfd[0]).detach();
    } catch (std::system_error &e){
        close(outfd[0]);
        close(errfd[0]);
        wxLogError("Failed to start thread to communicate with process %d, message: %s", pid, e.what());
        result = -1;
    }
    return result;
}

void Process::Loop(wxWindow *term, int pid, int outfd, int errfd) {
    char *buff = new char[1024];
    int n = 2;
    pollfd fds[2];
    fds[0].fd = outfd;
    fds[1].fd = errfd;
    fds[0].events = POLLIN;
    fds[1].events = POLLIN;
    int ret = poll(fds, 2, 500);
    while(ret > -1 && n > 0) {
        for(int i = 0; i < 2; i++) {
            if(fds[i].revents & POLLIN) {
                int size = read(fds[i].fd, buff, 1023);
                if(n > 0) {
                    buff[size] = 0;
                    SendEvent(term, buff, i);
                }
            } else if(fds[i].revents & POLLHUP || fds[i].revents & POLLNVAL) {
                close(fds[i].fd);
                fds[i].fd = -1;
                n--;
            } else if(fds[i].revents != 0){
                std::stringstream ss;
                ss << "fd: " << i << " event: " << fds[i].revents << "\n";
                SendEvent(term, ss.str(), 1);
            }
        }
        ret = poll(fds, 2, 500);
    }
    close(outfd);
    close(errfd);
    SendEvent(term, "", 2);
    int status = 0;
    int result = waitpid(pid, &status, 0);
    delete[] buff;
}

void Process::SendEvent(wxWindow *wind, const std::string &msg, int select) {
    auto evt = wxThreadEvent(wxEVT_THREAD, Process::EVENT::WRITE + select);
    evt.SetString(msg);
    wxQueueEvent(wind, evt.Clone());
}

int Process::Execute(const std::string &cmd, const std::vector<std::string> &args) {
    pid = fork();
    if(pid == 0) exit(RunCommand(cmd, args));
    if(pid > 0) return PollCommand();
    wxLogError("Failed to start process %s", cmd);
    close(outfd[0]);
    close(outfd[1]);
    close(errfd[0]);
    close(errfd[1]);
    return -1;
}