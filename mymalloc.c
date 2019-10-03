//
//  main.c
//  project1-systems-214
//
//  Created by Alexander Goodkind on 10/1/19.
//  Copyright © 2019 Alex Goodkind. All rights reserved.
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

    // myblock[0] = test;

//    ((MemNode*)(ptr))->inUse = 1;

    void* mallocTest = (void*)calloc(1, 10);




    printf("%s", "hello!\n");

    // free(mallocTest);

    return 0;

}


void* mymalloc (size_t size) {
  if(size + globalSize + (nodeCount * 8)>sizeOfHeap)
  {
    return NULL;
  }
  char *currentPos = myblock;
  int i;
  for(i = 0; i<nodeCount; i++)
  {
    if(((node*)currentPos)->inUse==0&&((node*)currentPos)->blockSize>=size)
    {
      return currentPos;
    }
    currentPos += ((node*)currentPos)->blockSize + sizeof(node*)+1;
  }
  if(i>=nodeCount)
  {
    return NULL;
  }

    return 0;

}
void combineFreeBlocks(byte* heap)
{
  /*traverse the block of memory and locating the adjacent free blocks, combining their
  sizes along the way*/
}

void myfree (void* address) {
  char* currentPos = myblock;
  int i;
  for(i = 0; i<nodeCount; i++)
  {
    if(currentPos+sizeof(node*)+1==address)
    {
      ((node*)currentPos)->inUse = 0;
      combineFreeBlocks(myblock);
      return;
      //break;
    }
    currentPos += ((node*)currentPos)->blockSize + sizeof(node*)+1;
  }

}
