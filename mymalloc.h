//
//  mymalloc.h - main program header
//  Rutgers CS 01:198:214 Systems Programming
//  Professor John-Austen Francisco
//  Authors: Anthony Siluk & Alexander Goodkind
//  Due: 10/15/2019
//

#ifndef _MYMALLOC_H
#define _MYMALLOC_H

#define malloc( x ) mymalloc( ( x ) , __FILE__, __LINE__ )
#define free( x ) myfree( ( x ) , __FILE__ , __LINE__ )

#define HEAP_SIZE 4096

#if DEBUG
void debug(void);
#endif

typedef unsigned long size_t;

typedef struct _node {
    int inUse;
    size_t blockSize;
} node;

typedef enum _bool {
    true = 1,
    false = 0
} bool;

static char myblock[HEAP_SIZE];

char* findOpenBlock (size_t);
void* mymalloc (size_t, char*, int);
void myfree (void*, char*, int);
void combineFreeBlocks (void);
void* splitBlock (char*, size_t);
char* getNext(char*);


#endif /* _MYMALLOC_H */
