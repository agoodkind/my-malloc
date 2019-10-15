/**
 mymalloc.c - library program
 Rutgers CS 01:198:214 Systems Programming
 Professor John-Austen Francisco
 Authors: Anthony Siluk & Alexander Goodkind
 Due: 10/15/2019
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "mymalloc.h"

static char myblock[HEAP_SIZE];

bool heapUninitialized = true;

void * mymalloc(size_t size, char *file, int line) {
    
    char *openNode;
    
    if (size > 4096-sizeof(node)) {
        printf("%s%d: Error not enough memory\n", file, line);
        return NULL;
    }
    
    if (heapUninitialized == true) {
        /* get the top of heap ready to accept allocations we set the very beginning of the heap to true*/
        ((node *)&myblock[0])->inUse = inUseBoolToChar(false);
        ((node *)&myblock[0])->blockSize = 4096 - (sizeof(node)) - 1;

        heapUninitialized = false;
    }

    openNode = findOpenNode(size);

    if (openNode == NULL) {
        printf("%s%d: Error not enough memory\n", file, line);
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
    size_t newSize = 0;
    char *currentNode = &myblock[0];
    char *nextNode = NULL;
    
    /* scan entire heap until we reach the end (or hit NULL for some edge case) */
    while (currentNode < &myblock[4096] && currentNode != NULL) {
        if (!isInUse(((node *)currentNode))){
            nextNode = getNext(currentNode);
            
            /* reached the end of the memory heap */
            if (nextNode >= &myblock[4096] || nextNode == NULL) {
                return;
            }
            
            /* add up the blockSize of the nextNode + the size of the metadata */
            newSize += sizeof(node) + ((node*)nextNode)->blockSize + 1;

            if (!isInUse(((node *)nextNode))) {
                ((node *)currentNode)->blockSize += newSize;
                newSize = 0;
                nextNode = getNext(nextNode);
            } else {
                currentNode = getNext(currentNode);
            }
        } else {
            
            currentNode = getNext(currentNode);
        }
    }
}

/**
 this function takes in a void pointer and searches the memory block for the corresponding metadata node then marks it as not in use
 it then calls combineFreeBlocks(); which combines all adjacent blocks that have been marked as not in use, such that the very first of the next n free blocks contains the sum of all their corresponding sizes
 */
void myfree(void *address, char *file, int line) {
    
    char *currentPos;
    char *userAddress;
    
    /* a NULL address is already free by definition */
    if (address == NULL) {
        return;
    }
    
    currentPos = &myblock[0];
    userAddress =  (char *)((char *)address - sizeof(node) - 1);
    
    while (currentPos < &myblock[4096]) {
        if (currentPos == userAddress) {
            if (!isInUse(((node *)currentPos))) {
                printf("%s:%d Error specified address was already freed\n", file, line);
                return;
            }
            ((node *)currentPos)->inUse = inUseBoolToChar(false);
            combineFreeBlocks();
            return;
        }

        currentPos = getNext(currentPos);
    }
    printf("%s:%d Error no memory has yet been allocated\n", file, line);
    return;
}

/**
 this function starts at the beginning of the array and looks for a free space that contains enought to hold the combination of:
 the metadata, the user requested size, and 1 additional byte
 */

char * findOpenNode(size_t size) {
    char *current = &myblock[0];
    size_t sizeNeeded = sizeof(node) + size + 1;

    while (current < &myblock[4096]) {
        if (!isInUse(((node *)current)) &&
            ((node *)current)->blockSize >= sizeNeeded) {
            return current;
        }

        current = getNext(current);
    }

    return NULL;
}

/**
 get the next node, this is the current pointer + blockSize + sizeof(node) + 1
 */
char * getNext(char *current) {
    /* get the max_heap (the pointer of the very last index of the heap */

    char *max_heap = &myblock[HEAP_SIZE];
    
    char *next = current + ((node *)current)->blockSize + sizeof(node) + 1;

    /* using pointer arithmetic compare the next node with the last pointer of the heap */
    /* we cant return anything past the end of the heap so we return NULL */

    if (next >= max_heap) {
        return NULL;
    } else {
        return next;
    }
}

/**
this function only gets called if a block was found with enough space
 we take the block that was found to have a enough space and allocated space on it (set inUse = 't')
 we then designate an unused block directly adjacent to the end (of the size + header) of the given block
*/
void * splitBlock(char *current, size_t size) {
    size_t sizeNeeded = sizeof(node) + size + 1;
    size_t freeBlockSize = ((node *)current)->blockSize;
    size_t newBlockSize = freeBlockSize - sizeNeeded;
    
    /* we need a new node that starts adjacent to the current block */
    char *newNode = current + sizeNeeded;

    /* this block is now in use, mark this in our node */
    ((node *)current)->inUse = inUseBoolToChar(true);
    ((node *)current)->blockSize = size;

    /* set block size & inUse flag */
    ((node *)newNode)->blockSize = newBlockSize;
    ((node *)newNode)->inUse = inUseBoolToChar(false);

    /* return a void pointer to basePtr + the size of a node pointer + 1 stay consistent with malloc's implementation */
    return (void *)(current + sizeof(node) + 1);
}

/**
 inUse helper functions
 */
bool isInUse(node *node) {
    return inUseCharToBool(node->inUse);
}

char inUseBoolToChar(bool value) {
    if (value == false) {
        return 'f';
    } else {
        return 't';
    }
}

bool inUseCharToBool(char value) {
    if (value == 'f') {
        return false;
    } else {
        return true;
    }
}
