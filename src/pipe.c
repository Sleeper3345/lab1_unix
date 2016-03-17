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

	// ������� �����
	if (pipe(file_description) < 0) {
		fprintf(stderr, "������ PIPE-������\n");
		exit(EXIT_FAILURE);
	}


	if (sigaction(SIGPIPE, &act, NULL) == -1) {
		perror("������: �� ������� ���������� ������ SIGPIPE");
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();
	if (pid == 0) {
		// Child-�������
		close(file_description[1]);
		close(file_description[0]);
		exit(0);
	}
	else if (pid > 0) {
		//close(file_description[0]);
		sleep(1);

		size = write(file_description[1], string, 14);
		if (size != 14) {
			/* ���� ���������� ������� ���������� ����, �������� ��
			������ */
			printf("�� ���������� �������� ��� ������\n");
			exit(EXIT_FAILURE);
		}

		/* ������� ��������� �� pip'� 14 ���� � ������ ������, �.�. ���
		���������� ������ */
		size = read(file_description[0], resstring, 14);
		if (size < 0) {
			/* ���� ��������� �� ������, �������� �� ������ */
			printf("�� ���������� ��������� ������\n");
			exit(-1);
		}
		/* �������� ����������� ������ */
		printf("%s\n", resstring);
		/* ��������� ������� �����*/
		if (close(file_description[0]) < 0) {
			printf("�� ���������� ������� ������� �����\n");
		}
		/* ��������� �������� �����*/
		if (close(file_description[1]) < 0) {
			printf("�� ���������� ������� �������� �����\n");
		}

	}

	while (1) {}
}

void signal_pipe_handler(int signal, siginfo_t *siginfo, void *context) {

	if (signal == SIGPIPE)
		printf("SIGPIPE-������( %i )\n", signal);
}