all: find_dup

find_dup: find_dup.o test.o VectorSort.o
	g++ -o find_dup find_dup.o test.o VectorSort.o
