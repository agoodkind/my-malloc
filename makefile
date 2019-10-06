all: mymalloc.o memgrind.c
	gcc mymalloc.o memgrind.c

mymalloc.o: mymalloc.c
	gcc -o mymalloc.o -c mymalloc.c 
	
clean:
	rm -f a.out; rm -f mymalloc.o; rm -f debug_mymalloc
	
debug:
	gcc -D DEBUG=1 -g -Wall -o debug_mymalloc.o -c mymalloc.c
	gcc -D DEBUG=1 -g -Wall -o debug_mymalloc debug_mymalloc.o memgrind.c
