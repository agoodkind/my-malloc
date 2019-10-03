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
    
  if (size + globalSize + (nodeCount * sizeof(node*)) > HEAPSIZE) {
    return NULL;
  }
    
    node* currentPos = (node*)myblock;
    
    while (currentPos->next != NULL) {
        if (!currentPos->inUse) {
            
        } else {
            currentPos = currentPos->next;
        }
        
    }
    
  int i;
    
  for (i = 0; i < nodeCount; i++) {
      
    if (((node*)currentPos)->inUse == false && ((node*)currentPos)->blockSize >= size) {
        node* temp;
        
        return currentPos;
    }
      
    currentPos += ((node*)currentPos)->blockSize + sizeof(node*) + 1;
      
  }
    
  if (i >= nodeCount) {
    return NULL;
  }

 return 0;
}

void combineFreeBlocks(byte* heap) {
  /*traverse the block of memory and locating the adjacent free blocks, combining their
  sizes along the way*/
    int i;
  node* currentNode = (node*)myblock;
  node* nextNode = NULL;
  int accumulator = 0;
  for(i=0; i<nodeCount; i++)
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
    
  for(i = 0; i < nodeCount; i++) {
      
    if (currentPos + sizeof(node*) + 1 == address) {
        
      ((node*)currentPos)->inUse = 0;
      combineFreeBlocks(myblock);
        
      return;

    }
      
    currentPos += ((node*)currentPos)->blockSize + sizeof(node*)+1;
      
  }
    
}
