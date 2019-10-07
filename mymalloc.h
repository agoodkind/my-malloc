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

/**
 we use this node struct as the metadata
 char inUse: 't' = true
 'f' = false
 */
typedef struct _node {
    size_t blockSize;
    char inUse;
} node;

/**
 boolean is just false = 0, and true != 0 (1)
 for readibility sake
 */
typedef enum _bool {
    false = 0,
    true = 1
} bool;

static char myblock[HEAP_SIZE];

char* findOpenNode (size_t);
void* mymalloc (size_t, char*, int);
void myfree (void*, char*, int);
void combineFreeBlocks (void);
void* splitBlock (char*, size_t);
char* getNext(char*);
bool isInUse(node*);
char inUseBoolToChar(bool);
bool inUseCharToBool(char);

#endif /* _MYMALLOC_H */
