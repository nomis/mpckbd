/*
	2006-10-06 Simon Arlott
	http://simon.arlott.org/sw/mpckbd/
*/

#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void run(const char *cmd1, const char *cmd2);
void chvt(void);

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
			case MPCKBD_PREV: run("prev", NULL); children++; break;
			case MPCKBD_TOGGLE: run("toggle", NULL); children++; break;
			case MPCKBD_NEXT: run("next", NULL); children++; break;
			case MPCKBD_VOLUME_DOWN: run("volume", "-1"); children++; break;
			case MPCKBD_VOLUME_UP: run("volume", "+1"); children++; break;
			case KEY_PAUSE: chvt(); children++; break;
		}
	}
	return 1;
}

void run(const char *cmd1, const char *cmd2) {
	if (fork() != 0) return;

	close(0);
	close(1);
	close(2);

	execlp("mpc", "mpc", cmd1, cmd2, NULL);
	_exit(1);
}

void chvt(void) {
	if (fork() != 0) return;

	close(0);
	close(1);
	close(2);

	execlp("sudo", "sudo", "/usr/bin/chvt", "1", NULL);
	_exit(1);
}
