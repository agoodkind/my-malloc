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

int sizeOfHeap = 4096;
int nodeCount = 0;
int globalSize = 0;

int main(int argc, const char * argv[]) {

    node test;
    test.inUse = 1;
    test.blockSize = 10;

    printf("%s", "hello!\n");

    return 0;
}


void* mymalloc (size_t size) {
    
  if(size + globalSize + (nodeCount * 8)>sizeOfHeap) {
    return NULL;
  }
    
  char *currentPos = myblock;
    
  int i;
    
  for (i = 0; i<nodeCount; i++) {
      
    if (((node*)currentPos)->inUse == 0 && ((node*)currentPos)->blockSize >= size) {
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
}

void myfree (void* address) {
  char* currentPos = myblock;
  int i;
    
  for(i = 0; i < nodeCount; i++) {
      
    if (currentPos+sizeof(node*)+1 == address) {
        
      ((node*)currentPos)->inUse = 0;
      combineFreeBlocks(myblock);
        
      return;

    }
      
    currentPos += ((node*)currentPos)->blockSize + sizeof(node*)+1;
      
  }
    
}
