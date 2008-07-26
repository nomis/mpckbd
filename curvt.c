#include <stdio.h>
#include <linux/vt.h>
#include <sys/ioctl.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int vt = 0;
	struct vt_stat vts;

	vt = open("/dev/tty0",O_RDONLY);
	if (!vt)
		perror("open");
	else if (ioctl(vt, VT_GETSTATE, &vts) == 0)
		return vts.v_active;
	return 0;
}
