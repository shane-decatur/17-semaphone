all: control.o user.o
	gcc -o control control.o
	gcc -o write user.o

control.o: control.c control.h
	gcc -c control.c

user.o: user.c control.h
	gcc -c user.c
