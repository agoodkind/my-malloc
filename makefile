all: memgrind.c mymalloc.o
	gcc  memgrind.c mymalloc.o

mymalloc.o: mymalloc.c
	gcc -c mymalloc.c -o mymalloc.o
	
clean:
	rm a.out; rm mymalloc.o; rm debug_mymalloc
	
debug: mymalloc.c
	gcc -D DEBUG=1 mymalloc.c -o debug_mymalloc
