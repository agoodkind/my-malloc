//
//  mymalloc.h - main program header
//  Rutgers CS 01:198:214 Systems Programming
//  Professor John-Austen Francisco
//  Authors: Anthony Siluk & Alexander Goodkind
//  Due: 10/15/2019
//

#ifndef _mymalloc_h
#define _mymalloc_h

typedef unsigned long size_t;

typedef struct _node {
    int inUse;
    size_t blockSize;
    struct node* next;
} node;

typedef enum _bool {
    true = 1,
    false = 0
} bool;

typedef char byte;

static const int HEAPSIZE = 4096;
static int nodeCount = 0;
static int globalSize = 0;
static byte myblock[HEAPSIZE];

void* mymalloc(size_t);
void myfree(void *);
void combineFreeBlocks();




#endif /* _mymalloc_h */
