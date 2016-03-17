#include "lab1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void std_mode() {
	struct sigaction act;
	act.sa_sigaction = &signal_std_handler;

	act.sa_flags = SA_SIGINFO;

	sigfillset(&act.sa_mask);

	if (sigaction(SIGHUP, &act, NULL) == -1) {
		perror("Can't read SIGHUP");
	}
	if (sigaction(SIGUSR1, &act, NULL) == -1) {
		perror("Can't read SIGUSR1");
	}
	if (sigaction(SIGUSR2, &act, NULL) == -1) {
		perror("Can't read SIGUSR2");
	}
	while (1) sleep(1);
}

void signal_std_handler(int signal, siginfo_t *siginfo, void *context)
{
	char* name;

	if (signal == SIGUSR1)
		name = "SIGUSR1";
	else
		if (signal == SIGUSR2)
			name = "SIGUSR2";
		else
			if (signal = SIGHUP)
				name = "SIGHUP";
	pid_t pid = siginfo->si_pid;
	fprintf(stderr, "Signal %s. PID: %i, GID: %i \n", name, pid, getpgid(pid));
}
