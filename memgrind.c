//
//  memgrind.c - mymalloc tester filer
//  Rutgers CS 01:198:214 Systems Programming
//  Professor John-Austen Francisco
//  Authors: Anthony Siluk & Alexander Goodkind
//  Due: 10/15/2019
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>

#include "mymalloc.h"
#include "memgrind.h"

int main(int argc, const char *argv[]) {
#if DEBUG

    //printf("%X", (unsigned int)((node*)myblock)->next);

    char *testCharArrayFive = (char *)malloc(5 * sizeof(char));

    testCharArrayFive = "hell";

    int *testIntArraySeven = (int *)malloc(7 * sizeof(int));

    testIntArraySeven[0] = 1;
    testIntArraySeven[6] = 6969420;

    free(testCharArrayFive);

    long *testLongArrayTen = (long *)malloc(10 * sizeof(long));

    testLongArrayTen[0] = 192319230913;
    testLongArrayTen[9] = 999999999999;

    free(testIntArraySeven);

    free(testLongArrayTen);

    printf("test\n");

#endif
    
    char *character = (char *)malloc(sizeof(char));
    *character = 'A';
    printf("this is character = %c\n", *character);
    free(character);
    printf("this is character = %c\n", *character);

    /*int i;
    for(i = 0; i<151; i++)
    {

    }*/

    return 0;
}
