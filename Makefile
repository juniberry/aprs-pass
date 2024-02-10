CC=gcc
CFLAGS=-Wall -g

all: aprsispass

aprs_passcode_gen: aprsispass.c
	$(CC) $(CFLAGS) aprsispass.c -o aprsispass

clean:
	rm -f aprs_passcode_gen
