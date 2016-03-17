#include <lab1.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

struct globalArgs_t {
	char *mode; // mode=Режим
	int amount; // Работает вместе с mode=posix
	int signalName;
	pid_t pidVal;
} globalArgs;

static const struct option long_options[] = {
	{ "mode", required_argument, NULL, 0 },
	{ "amount", required_argument, NULL, 0 },
	{ "signal", required_argument, NULL, 0 },
	{ "pid", required_argument, NULL, 0 }
};

int main(int argc, char *argv[]) {
	int opt = 0;
	int longIndex = 0;

	// Инициализация параметров перед использованием
	globalArgs.mode = NULL;
	globalArgs.amount = 0;
	globalArgs.signalName = 0;
	globalArgs.pidVal = 0;

	opt = getopt_long(argc, argv, "", long_options, &longIndex);
	while (opt != -1) {
		if (strcmp("mode", long_options[longIndex].name) == 0) {
			globalArgs.mode = optarg;
		}
		else if (strcmp("signal", long_options[longIndex].name) == 0) {
			globalArgs.signalName = atoi(optarg);
		}
		else if (strcmp("amount", long_options[longIndex].name) == 0) {
			globalArgs.amount = atoi(optarg);
		}
		else if (strcmp("pid", long_options[longIndex].name) == 0) {
			globalArgs.pidVal = atoi(optarg);
		}
		opt = getopt_long(argc, argv, "", long_options, &longIndex);
	}

	run_with_parameters();
	return EXIT_SUCCESS;
}

void run_with_parameters() {
	if (strcmp(globalArgs.mode, "std") == 0) {
		// Запуск программы для обработки сигналов SIGUSR1, SIGUSR2, SIGHUP
		std_mode();
	}
	else if (strcmp(globalArgs.mode, "child") == 0) {
		// Запуск программы для обработки сигнала SIGCHLD
		child_mode();
	}
	else if (strcmp(globalArgs.mode, "posix") == 0) {
		// Запуск программы для обработки POSIX-сигналов
		if (globalArgs.amount != 0) {
			posix_mode(globalArgs.amount);
		}
		else {
			printf("Count of POSIX signals cannot be 0\n");
		}
	}
	else if (strcmp(globalArgs.mode, "kill") == 0) {
		// Запуск программы для посыла сигналов процессу, группам процессов с указанием сигнала
		if (!globalArgs.pidVal) {
			fprintf(stderr, "You didn't enter the process\n");
			exit(EXIT_FAILURE);
		}

		if (!globalArgs.signalName) {
			fprintf(stderr, "You didn't enter the signal\n");
			exit(EXIT_FAILURE);
		}

		kill_mode(globalArgs.signalName, globalArgs.pidVal);
	}
	else if (strcmp(globalArgs.mode, "pipe") == 0) {
		// Запуск программы для обработки сигнала SIGCHLD
		pipe_mode();
	}
	else {
		fprintf(stderr, "You entered an unright argument\n");
		exit(EXIT_FAILURE);
	}

}
