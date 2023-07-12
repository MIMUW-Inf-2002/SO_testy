#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define N 10

int
main(void)
{
	int pid[2 * N];

	for (int i = 0; i < 2 * N; ++i) {
		pid[i] = fork();
		if (!pid[i]) {
			wait_for_sibling();
			wait_for_parent();
			return 0;
		}
	}
	
	usleep(100 * 1000);
	wait_for_child();

	for (int i = 0; i < 2 * N; ++i) {
		waitpid(pid[i], NULL, 0);
	}

	return 0;
}
