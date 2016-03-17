#include "lab1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int number = 0;

void posix_mode(int amount) {
	struct sigaction act;
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &signal_posix_handler;

	sigset_t set;

	if (sigaction(SIGRTMIN, &act, NULL) == -1) {
		perror("Can't read SIGRTMIN");
	}

	int j = 0;
	for (j = 0; j < SIGRTMAX; j++) {
		sigaction(SIGRTMIN + j, &act, NULL);
	}

	pid_t pid = fork();
	if (pid == 0) {
		int i = 0;

		int range = 1 + SIGRTMAX - SIGRTMIN;
		int buckets = RAND_MAX / range;
		int limit = buckets * range;

		for (i = 0; i < amount; ++i) {
			union sigval value;

			int r_signal;
			do {
				r_signal = rand();
			} while (r_signal >= limit);

			r_signal = SIGRTMIN + (r_signal / buckets);

			value.sival_int = rand();





			sigqueue(getppid(), r_signal, value);
			fprintf(stderr, "CHILD: N=%i | MYPID=%i | PPID=%i | POSIXSIGNALNO=%i | VALUE=%i\n",
				i, getpid(), getppid(), r_signal, value.sival_int);
		}
	}
	else if (pid > 0) {
		printf("Parent: PID=%d, GID=%d\n", getpid(), getpgid(getpid()));
		sleep(5);

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

void signal_posix_handler(int signal, siginfo_t *siginfo, void *context) {

	fprintf(stderr, "PARENT: N=%i | MYPID=%i | PPID=%i | POSIXSIGNALNO=%i | VALUE=%i\n",
		number, siginfo->si_pid, getpid(), signal, siginfo->si_value.sival_int);
	number++;
}
