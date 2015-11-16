project: libman.o 
		cc libman.o -o project
libman.o: libman.c 
		cc -Wall -c libman.c

