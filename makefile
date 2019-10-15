all: mymalloc.o memgrind.c
	gcc -O0 -std=gnu89 mymalloc.o memgrind.c

mymalloc.o: mymalloc.c
	gcc -O0 -std=gnu89 -o mymalloc.o -c mymalloc.c
	
clean:
	rm -f a.out; rm -f mymalloc.o; rm -f debug_mymalloc; rm -rf *.a; rm -rf *.o; rm -rf *.dSYM;
	
debug:
	gcc -O0 -std=gnu89 -pedantic -D DEBUG=1 -g -Wall -o debug_mymalloc.o -c mymalloc.c
	gcc -O0 -std=gnu89 -pedantic -D DEBUG=1 -g -Wall -o debug_mymalloc debug_mymalloc.o memgrind.c
