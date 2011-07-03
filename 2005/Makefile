all: 1 2 3 6 8

INCLUDE=../include

1: 1.C
	g++ -Wall 1.C -o 1

2: 2.c
	gcc -Wall --std=c99 2.c -o 2

3: 3.cc
	g++ -Wall -I${INCLUDE} 3.cc -o 3

6: 6.cc
	g++ -Wall -I${INCLUDE} 6.cc -o 6

8: 8.cc
	g++ -Wall  -I${INCLUDE} 8.cc -o 8
