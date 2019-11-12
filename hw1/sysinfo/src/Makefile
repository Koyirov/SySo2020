# Makefile
CC=gcc
R=rm
CFLAGS=-static

target=../../artifacts/sysinfo

sysinfo: sysinfo.c
	$(CC) $(CFLAGS) sysinfo.c -o $(target)

clean:
	$(R) -f $(target)
