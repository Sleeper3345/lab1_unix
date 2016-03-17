#include "lab1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void pipe_mode() {
	int file_description[2];
	struct sigaction act;
	size_t size;
	char string[] = "Hello, world!";
	char resstring[14];
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &signal_pipe_handler;

	// Открыть канал
	if (pipe(file_description) < 0) {
		fprintf(stderr, "Ошибка PIPE-потока\n");
		exit(EXIT_FAILURE);
	}


	if (sigaction(SIGPIPE, &act, NULL) == -1) {
		perror("Ошибка: не удается обработать сигнал SIGPIPE");
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();
	if (pid == 0) {
		// Child-процесс
		close(file_description[1]);
		close(file_description[0]);
		exit(0);
	}
	else if (pid > 0) {
		//close(file_description[0]);
		sleep(1);

		size = write(file_description[1], string, 14);
		if (size != 14) {
			/* Если записалось меньшее количество байт, сообщаем об
			ошибке */
			printf("Не получается записать всю строку\n");
			exit(EXIT_FAILURE);
		}

		/* Пробуем прочитать из pip'а 14 байт в другой массив, т.е. всю
		записанную строку */
		size = read(file_description[0], resstring, 14);
		if (size < 0) {
			/* Если прочитать не смогли, сообщаем об ошибке */
			printf("Не получается прочитать строку\n");
			exit(-1);
		}
		/* Печатаем прочитанную строку */
		printf("%s\n", resstring);
		/* Закрываем входной поток*/
		if (close(file_description[0]) < 0) {
			printf("Не получается закрыть входной поток\n");
		}
		/* Закрываем выходной поток*/
		if (close(file_description[1]) < 0) {
			printf("Не получается закрыть выходной поток\n");
		}

	}

	while (1) {}
}

void signal_pipe_handler(int signal, siginfo_t *siginfo, void *context) {

	if (signal == SIGPIPE)
		printf("SIGPIPE-сигнал( %i )\n", signal);
}