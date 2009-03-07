#INCLUDES=-I/usr/src/linux/include

PREV=KEY_POWER
TOGGLE=KEY_SLEEP
NEXT=KEY_WAKEUP
VOLUME_UP=KEY_RIGHTMETA
VOLUME_DOWN=KEY_LEFTMETA

mpckbd: mpckbd.c Makefile
	gcc -o mpckbd mpckbd.c -O2 -Wall -Werror \
		-DMPCKBD_PREV=$(PREV) \
		-DMPCKBD_TOGGLE=$(TOGGLE) \
		-DMPCKBD_NEXT=$(NEXT) \
		-DMPCKBD_VOLUME_UP=$(VOLUME_UP) \
		-DMPCKBD_VOLUME_DOWN=$(VOLUME_DOWN) \
		$(INCLUDES)

curvt: curvt.c Makefile
	gcc -o curvt curvt.c -O2 -Wall -Werror

clean:
	rm -f mpckbd curvt
