//
//  mymalloc.c - main program
//  Rutgers CS 01:198:214 Systems Programming
//  Professor John-Austen Francisco
//  Authors: Anthony Siluk & Alexander Goodkind
//  Due: 10/15/2019
//

#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

void* mymalloc (size_t size) {
    
    node* currentBlock = (node*)myblock;
    
    // case 1: the first block is NULL, which means our entire list is free
    if (currentBlock != NULL) {
        while (currentBlock->next != NULL) {

            if (currentBlock->blockSize >= size + sizeof(node*) + 1) {
              return splitBlock(currentBlock, size);
            }

            currentBlock = currentBlock->next;
        }

        // print error out of mem
    }

    return NULL;

}

void combineFreeBlocks()
{
  /*traverse the block of memory and locating the adjacent free blocks, combining their
  sizes along the way*/
  int i;
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
    //currentNode = (node*)currentNode;
    currentNode->blockSize += accumulator;
    currentNode = nextNode;
    accumulator = 0;
  }
}

void myfree (void* address) {
  char* currentPos = myblock;
  int i;
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

void* splitBlock (node* block, size_t size) {
    
    size_t sizeNeeded = sizeof(node*) + size + 1;
    void* userPointer;
    
    if (block->blockSize >= sizeNeeded) {
        
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
        
    } else {
        userPointer = NULL;
    }
    
    return userPointer;
}
