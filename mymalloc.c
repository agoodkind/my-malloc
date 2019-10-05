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


void* mymalloc (size_t size, char* file, int line) {
    
    if (heapUninitialized) {
        /**
        get the top of heap ready to accept allocations
        */
        
        node* head = ((node*)myblock);
        head->blockSize = 4096 - (sizeof(node*)) - 1;
        head->inUse = false;
        
        heapUninitialized = false;
    }
    
    node* currentBlock = (node*)myblock;
    size_t sizeNeeded = sizeof(node*) + size + 1;

    while (currentBlock != NULL) {
      if (currentBlock->blockSize >= sizeNeeded) {
        return splitBlock(currentBlock, size);
      }

      currentBlock = currentBlock->next;
    }

    // print error out of mem

    return NULL;
}

void combineFreeBlocks()
{
  /**
   traverse the block of memory and locating the adjacent free blocks, combining their
  sizes along the way
   */
  node* currentNode = (node*)myblock;
  node* nextNode = NULL;
  int accumulator = 0;
  if(currentNode==NULL)
  {
    return;
  }
  while(currentNode!=NULL)
  {
    if(currentNode->inUse==0)
    {
      nextNode = currentNode->next;
      if(nextNode->inUse==0)
      {
        accumulator+=nextNode->blockSize;
        continue;
      }
    }
    // currentNode = (node*)currentNode;
    currentNode->blockSize += accumulator;
    currentNode = nextNode;
    accumulator = 0;
  }
}

void myfree (void* address, char* file, int line) {
  char* currentPos = myblock;
  if(currentPos==NULL)
  {
    printf("Error no memory has yet been allocated\n");
    return;
  }
  while(currentPos!=NULL)
  {
    if(((node*)currentPos)->next==address)
    {
      if(((node*)currentPos)->inUse==0)
      {
        printf("Error specified address was already freed\n");
        return;
      }
      ((node*)currentPos)->inUse = 0;
      combineFreeBlocks();
      return;
      //break;
    }
    //currentPos += ((node*)currentPos)->blockSize + sizeof(node*)+1;
    currentPos = ((node*)currentPos)->next;
  }

}

/**
this function only gets called if a block was found with enough space
*/
void* splitBlock (node* block, size_t size) {
    
    size_t sizeNeeded = sizeof(node*) + size + 1;
    void* userPointer;
        
    // this block is now in use, mark this in our node
    block->inUse = true;
    block->blockSize = size;
    
    // we need a new block
    (block + size + 1)->next = block->next;
    block->next = (block + size + 1);
    
    size_t newBlockSize = 0;
    
    // case 1: block has exactly enough space for a new block of memory + requested size + 1
    if (block->blockSize == sizeNeeded) {
        newBlockSize = 1;
        
    // case 2: block has enough space for a new block of memory + requested size + n
    } else if (block->blockSize > sizeNeeded) {
        newBlockSize = block->blockSize - sizeNeeded;
    }
    
    block->next->blockSize = newBlockSize;
    
    userPointer = (void*)(block + 1);
    
    return userPointer;
}



