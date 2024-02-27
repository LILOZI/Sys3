# Flags and commands
CC = gcc
AR = ar
CFLAGS = -Wall -g
AFLAGS = rcs
FP = -fPIC

.PHONY: all clean

all: StrList

StrList: Main.o StrLib.a
	$(CC) $(CFLAGS) -o StrList Main.o ./StrLib.a 
# gcc -Wall -g -o StrList Main.o ./StrLib.a

Main.o: Main.c StrList.h
	$(CC) $(CFLAGS) -c $<
# gcc -Wall -g -c Main.c -o Main.o

StrLib.a: StrList.o
	$(AR) $(AFLAGS) $@ $<
# ar rc StrLib.a Strlib.o ranlib Strlib.a

StrList.o: StrList.c StrList.h
	$(CC) $(CFLAGS) -c $<
# gcc -Wall -g  -c StrList.c -o StrList.o, $< means the first prerequistie in the dependency list here


clean:
	rm -f *.o *.a StrList StrLib.a