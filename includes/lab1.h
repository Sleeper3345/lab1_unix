#ifndef __LAB__
#define __LAB__
#include <signal.h>

#define CHILD_SLEEP_TIME 3

void run_with_parameters();

void kill_mode(int signal, pid_t k_pid);
void std_mode();
void child_mode();
void pipe_mode();
void posix_mode(int amount_of_signals);

void signal_std_handler(int signal, siginfo_t *siginfo, void *context);
void signal_child_handler(int signal, siginfo_t *siginfo, void *context);
void signal_posix_handler(int signal, siginfo_t *siginfo, void *context);
void signal_pipe_handler(int signal, siginfo_t *siginfo, void *context);

#endif