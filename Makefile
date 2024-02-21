all: StrList

StrList: StrList.a
	gcc -Wall -g Main.o StrList.o -o StrList

StrList.a: Main.o StrList.o
	ar -rcs StrList.a Main.o StrList.o

Main.o: Main.c StrList.h
	gcc -Wall -g -c Main.c

StrList.o: StrList.c StrList.h
	gcc -Wall -g -c StrList.c



.PHONY: all clean

clean:
	rm -f *.o StrList *.a