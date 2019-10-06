//
//  mymalloc.c - library program
//  Rutgers CS 01:198:214 Systems Programming
//  Professor John-Austen Francisco
//  Authors: Anthony Siluk & Alexander Goodkind
//  Due: 10/15/2019
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "mymalloc.h"

bool heapUninitialized = true;

#if DEBUG
void debug() {
    
}
#endif

/**
 TODO: add bound checking
 */

void* mymalloc (size_t size, char* file, int line) {
    
    if (heapUninitialized == true) {
        /**
        get the top of heap ready to accept allocations
         we set the very beginning of the heap to true
        */
        
        ((node*)&myblock[0])->inUse = false;
        ((node*)&myblock[0])->blockSize = 4096 - (sizeof(node*)) - 1;
        
        heapUninitialized = false;
    }
    
    char* openNode = findOpenBlock(size);
    
    if (openNode == NULL) {
        return NULL;
    } else {
        return splitBlock(openNode, size);
    }
   
}

/**
 traverse the block of memory and locating the adjacent free blocks, combining their
sizes along the way
 */
void combineFreeBlocks() {
  char* currentNode = myblock;
  char* nextNode = NULL;
  int accumulator = 0;
    
  if(currentNode == NULL) {
    return;
  }
    
  while(currentNode!=NULL)
  {
    if(((node*)currentNode)->inUse==0)
    {
      nextNode = getNext(currentNode);
      if(((node*)currentNode)->inUse==0)
      {
        accumulator += ((node*)currentNode)->blockSize;
        continue;
      }
    }
      
    ((node*)currentNode)->blockSize += accumulator;
    currentNode = nextNode;
    accumulator = 0;
  }
}

/**
 TODO: add checking for pointer input
 we must assert that &myblock[0] <= (char*) address <= &myblock[HEAP_SIZE]
 or error out
 */
void myfree (void* address, char* file, int line) {
  char* currentPos = myblock;
  if(currentPos==NULL)
  {
    printf("Error no memory has yet been allocated\n");
    return;
  }
  while(currentPos!=NULL)
  {
    if(getNext(currentPos) == address)
    {
      if(((node*)currentPos)->inUse==0)
      {
        printf("Error specified address was already freed\n");
        return;
      }
      ((node*)currentPos)->inUse = 0;
      combineFreeBlocks();
      return;

    }

    currentPos = getNext(currentPos);
  }

}

/**
 this function starts at the beginning of the array and looks for a free space that contains enought to hold the combination of:
 the metadata, the user requested size, and 1 additional byte
 */

char* findOpenBlock(size_t size) {
    char* current = &myblock[0];
    size_t sizeNeeded = sizeof(node*) + size + 1;

    while (current != NULL) {
      if (!((node*)current)->inUse &&
          ((node*)current)->blockSize >= sizeNeeded) {
          return current;
      }

        current = getNext(current);
    }
    
    return NULL;
}
/**
 get the next node, this is the current pointer + blockSize + sizeof(node*) + 1
 */
char* getNext(char* current) {
    
    // get the max_heap (the pointer of the very last index of the heap
    
    char* max_heap = &myblock[HEAP_SIZE];
    char* next = current + ((node*)current)->blockSize + sizeof(node*) + 1;
    
    
    // using pointer arithmetic compare the next node with the last pointer of the heap
    // we cant return anything past the end of the heap so we return NULL
    
    if (next >= max_heap) {
        return NULL;
    } else {
        return next;
    }
    
}

/**
this function only gets called if a block was found with enough space
 we take the block that was found to have a enough space and allocated space on it (set inUse = true)
 we then designate an unused block directly adjacent to the end (of the size + header) of the given block
*/
void* splitBlock (char* current, size_t size) {
    
    size_t sizeNeeded = sizeof(node*) + size + 1;
    size_t freeBlockSize = ((node*)current)->blockSize;
    size_t newBlockSize = freeBlockSize - sizeNeeded;
        
    // this block is now in use, mark this in our node
    ((node*)current)->inUse = true;
    ((node*)current)->blockSize = size;
    
    // we need a new node that starts adjacent to the current block
    char* newNode = current + sizeNeeded;
    
    // set block size & inUse flag
    ((node*)newNode)->blockSize = newBlockSize;
    ((node*)newNode)->inUse = false;

    // return a void pointer to basePtr + the size of a node pointer + 1 stay consistent with malloc's implementation
    return (void*)(current + sizeof(node*) + 1);
}



