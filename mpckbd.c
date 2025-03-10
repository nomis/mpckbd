/*
	2006-10-06 Simon Arlott
	http://simon.arlott.org/sw/mpckbd/
*/

#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void run(const char *cmd);

int main() {
	struct input_event event;
	int status;
	int children = 0;

	while (read(0, &event, sizeof(event)) > 0) {
		if (children > 0) {
			if (waitpid(-1, &status, WNOHANG) > 0)
				children--;
		}
		if (event.type != EV_KEY) continue;
		if (event.value != EV_KEY) continue;

		switch (event.code) {
			case MPCKBD_PREV: run("_music-prev"); children++; break;
			case MPCKBD_TOGGLE: run("_music-toggle"); children++; break;
			case MPCKBD_NEXT: run("_music-next"); children++; break;
		}
	}
	return 1;
}

void run(const char *cmd) {
	if (fork() != 0) return;

	close(0);
	close(1);
	close(2);

	execlp(cmd, cmd, NULL);
	_exit(1);
}
