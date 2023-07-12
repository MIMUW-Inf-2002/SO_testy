#include <unistd.h>
#include <stdio.h>

#define D 10

int
main(void)
{
	int depth = 1;
	int pid;

i_love_goto:
	printf("%d\n", depth);
	pid = (depth < D ? fork() : 1);

	if (pid) {
		if (depth < D) {
			wait_for_child();
		}
		if (depth > 1) {
			wait_for_parent();
		}
		return 0;
	}

	depth++;
	goto i_love_goto;
}
