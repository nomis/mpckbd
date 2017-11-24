PREV=KEY_PREVIOUSSONG
TOGGLE=KEY_PLAYPAUSE
NEXT=KEY_NEXTSONG

mpckbd: mpckbd.c Makefile
	gcc -o mpckbd mpckbd.c -O2 -Wall -Werror \
		-DMPCKBD_PREV=$(PREV) \
		-DMPCKBD_TOGGLE=$(TOGGLE) \
		-DMPCKBD_NEXT=$(NEXT)

clean:
	rm -f mpckbd
