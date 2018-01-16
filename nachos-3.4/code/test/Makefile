# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as

GCCDIR = ../../../cross-compiler/decstation-ultrix/bin/
LDFLAGS = -T script -N
ASFLAGS = -mips2
CPPFLAGS = $(INCDIR)
# if you aren't cross-compiling:
# GCCDIR =
# LDFLAGS = -N -T 0
# ASFLAGS =
# CPPFLAGS = -P $(INCDIR)
PATH = $(GCCDIR):/lib:/usr/bin:/bin
CC = $(GCCDIR)gcc -B../../../cross-compiler/
AS = $(GCCDIR)as
LD = $(GCCDIR)ld
CPP = gcc -E
INCDIR =-I../userprog -I../threads
CFLAGS = -G 0 -c $(INCDIR)

all: halt shell matmult sort bubblesort help ASCII createfile echo cat copy reverse idcard shell3 ping pong schedule

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.c > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	../bin/coff2noff shell.coff shell

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort

matmult.o: matmult.c
	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult

bubblesort.o: bubblesort.c
	$(CC) $(CFLAGS) -c bubblesort.c
bubblesort: bubblesort.o start.o
	$(LD) $(LDFLAGS) start.o bubblesort.o -o bubblesort.coff
	../bin/coff2noff bubblesort.coff bubblesort

help.o: help.c
	$(CC) $(CFLAGS) -c help.c
help: help.o start.o
	$(LD) $(LDFLAGS) start.o help.o -o help.coff
	../bin/coff2noff help.coff help

ASCII.o: ASCII.c
	$(CC) $(CFLAGS) -c ASCII.c
ASCII: ASCII.o start.o
	$(LD) $(LDFLAGS) start.o ASCII.o -o ASCII.coff
	../bin/coff2noff ASCII.coff ASCII

createfile.o: createfile.c
	$(CC) $(CFLAGS) -c createfile.c
createfile: createfile.o start.o
	$(LD) $(LDFLAGS) start.o createfile.o -o createfile.coff
	../bin/coff2noff createfile.coff createfile

echo.o: echo.c
	$(CC) $(CFLAGS) -c echo.c
echo: echo.o start.o
	$(LD) $(LDFLAGS) start.o echo.o -o echo.coff
	../bin/coff2noff echo.coff echo

cat.o: cat.c
	$(CC) $(CFLAGS) -c cat.c
cat: cat.o start.o
	$(LD) $(LDFLAGS) start.o cat.o -o cat.coff
	../bin/coff2noff cat.coff cat

copy.o: copy.c
	$(CC) $(CFLAGS) -c copy.c
copy: copy.o start.o
	$(LD) $(LDFLAGS) start.o copy.o -o copy.coff
	../bin/coff2noff copy.coff copy

reverse.o: reverse.c
	$(CC) $(CFLAGS) -c reverse.c
reverse: reverse.o start.o
	$(LD) $(LDFLAGS) start.o reverse.o -o reverse.coff
	../bin/coff2noff reverse.coff reverse

idcard.o: idcard.c
	$(CC) $(CFLAGS) -c idcard.c
idcard: idcard.o start.o
	$(LD) $(LDFLAGS) start.o idcard.o -o idcard.coff
	../bin/coff2noff idcard.coff idcard

shell3.o: shell3.c
	$(CC) $(CFLAGS) -c shell3.c
shell3: shell3.o start.o
	$(LD) $(LDFLAGS) start.o shell3.o -o shell3.coff
	../bin/coff2noff shell3.coff shell3

ping.o: ping.c
	$(CC) $(CFLAGS) -c ping.c
ping: ping.o start.o
	$(LD) $(LDFLAGS) start.o ping.o -o ping.coff
	../bin/coff2noff ping.coff ping

pong.o: pong.c
	$(CC) $(CFLAGS) -c pong.c
pong: pong.o start.o
	$(LD) $(LDFLAGS) start.o pong.o -o pong.coff
	../bin/coff2noff pong.coff pong

schedule.o: schedule.c
	$(CC) $(CFLAGS) -c schedule.c
schedule: schedule.o start.o
	$(LD) $(LDFLAGS) start.o schedule.o -o schedule.coff
	../bin/coff2noff schedule.coff schedule
