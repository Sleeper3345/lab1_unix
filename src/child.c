#include "lab1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void child_mode() {
	struct sigaction act;
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &signal_child_handler;

	pid_t pid = fork();
	if (pid == 0) {
		printf("Child process: PID=%d, GID=%d\n", getpid(), getpgid(getpid()));
		sleep(CHILD_SLEEP_TIME);
	}
	else if (pid > 0) {
		printf("Parent process: PID=%d, GID=%d\n", getpid(), getpgid(getpid()));
		sigaction(SIGCHLD, &act, NULL);
		int status;
		if (wait(&status) > 0) {
			exit(EXIT_SUCCESS);
		}
		else {
			perror("Fail!!!");
			exit(EXIT_FAILURE);
		}
	}
}

void signal_child_handler(int signal, siginfo_t *siginfo, void *context) {
	switch (signal) {
	case SIGCHLD:
		printf("Parent: SIGCHLD. Child PID: %i. User: %i. Status: %i. Code: %i. \n", siginfo->si_pid, siginfo->si_uid, siginfo->si_status, siginfo->si_code);
		exit(EXIT_SUCCESS);
		break;
	default:
		fprintf(stderr, "I don't know this signal: %d\n", signal);
		return;
	}
}
