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

    testCharArrayFive[0] = 'h';
    testCharArrayFive[1] = 'e';
    testCharArrayFive[2] = 'l';
    testCharArrayFive[3] = 'l';
    testCharArrayFive[4] = '\0';

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

    char *character = (char *)malloc(sizeof(char));
    *character = 'A';
    printf("this is character = %c\n", *character);
    free(character);
    printf("this is character = %c\n", *character);
    
#endif
    
    int workload;
    for (workload = 0; workload < 150; workload++) {
        printf("Running workload #%d: \n", workload + 1);
        
        /**
         part A.)
         malloc() 1 byte and immediately free it - do this 150 times
         */
        printf("Part A.) Malloc and freeing 1 byte, 150 times.\n");
        int a;
        for (a = 0; a < 150; a++) {
            void* ptr = malloc(1);
            free(ptr);
        }
        printf("Done Part A.)\n");
        
        /**
         part B.)
         malloc() 1 byte, store the pointer in an array - do this 150 times.
         Once you've malloc()ed 50 byte chunks, then free() the 50 1 byte pointers one by one.
         TODO: what do we do with bytes 50-149
         */
        printf("Part B.) Malloc 1 byte, store the pointer in an array, 150 times.\nAfter 50 times, free 50 1 by 1.\n");
        int b;
        void* partB[150];
        for (b = 0; b < 150; b++) {
            partB[b] = malloc(1);
            if (b >= 50 && b < 100) {
                free(partB[b-50]);
            }
        }
        printf("Done Part B.)\n");
        
        /**
         part C.)
         Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer > do this until you have allocated 50 times
         - Keep track of each operation so that you eventually malloc() 50 bytes, in total
         > if you have already allocated 50 times, disregard the random and just free() on each
         iteration
         - Keep track of each operation so that you eventually free() all pointers
         > don't allow a free() if you have no pointers to free()
         TODO: random byte
         */
        printf("Part C.) Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer until 50 bytes have been allocated.\n");
        int numAllocated = 0;
        int numFreed = 0;
        
        /**
         part D.)
         Randomly choose between a randomly-sized malloc() or free()ing a pointer – do this many times (see below)
         - Keep track of each malloc so that all mallocs do not exceed your total memory capacity - Keep track of each operation so that you eventually malloc() 50 times
         - Keep track of each operation so that you eventually free() all pointers
         - Choose a random allocation size between 1 and 64 bytes
         
         */
        
        /**
         part E.)
         
         */
        
        /**
         part F.)
         
         */


        printf("Done Part C.)\n");
    }
    
    return 0;
}
