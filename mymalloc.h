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

typedef unsigned long size_t;

typedef struct _node {
    int inUse;
    size_t blockSize;
    struct _node* next;
} node;

typedef enum _bool {
    true = 1,
    false = 0
} bool;

typedef char byte;

static bool heapUninitialized = true;

static const int HEAPSIZE = 4096;
static byte myblock[HEAPSIZE];

void* mymalloc (size_t, char*, int);
void myfree (void*, char*, int);
void combineFreeBlocks (void);
void* splitBlock (node*, size_t);

#endif /* _MYMALLOC_H */
