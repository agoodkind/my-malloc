//
//  mymalloc.h
//  project1-systems-214
//
//

#ifndef mymalloc_h
#define mymalloc_h

typedef unsigned long size_t;

typedef struct _node {
    int inUse;
    size_t blockSize;
    //struct node* next;
} node;

typedef char byte;

static byte myblock[4096];

void* mymalloc(size_t);
void myfree(void *);
void combineFreeBlocks(byte*);




#endif /* mymalloc_h */
