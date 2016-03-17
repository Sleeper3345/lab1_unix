#include "lab1.h"
#include <stdio.h>
#include <signal.h>


void kill_mode(int signal, pid_t k_pid) {
	kill(k_pid, signal);
}