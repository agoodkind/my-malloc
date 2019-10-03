//
//  memgrind.c - mymalloc tester filer
//  Rutgers CS 01:198:214 Systems Programming
//  Professor John-Austen Francisco
//  Authors: Anthony Siluk & Alexander Goodkind
//  Due: 10/15/2019
//

/**
 debugger directive
 */
#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "memgrind.h"
#include "mymalloc.h"

int main(int argc, const char * argv[]) {

    node test;
    test.inUse = 1;
    test.blockSize = 10;

    char* testCharArrayFive = (char*)malloc(5*sizeof(char));
    
    int* testIntArraySeven = (int*)malloc(7*sizeof(int));
    
    printf("test\n");

    return 0;
}
