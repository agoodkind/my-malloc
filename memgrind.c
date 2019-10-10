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
         */
        printf("Part B.) Malloc 1 byte, store the pointer in an array, 150 times.\nAfter 50 times, free 50 1 by 1.\n");
        int b;
        void* partB[50];
        int partBCounter = 0;
        for (b = 0; b < 150; b++) {
            partB[partBCounter++] = malloc(1);
            if (partBCounter == 50) {
                int b2;
                for (b2 = 0; b2 < 50; b2++) {
                    free(partB[b2]);
                    partB[b2] = NULL;
                }
                partBCounter = 0;
            }
        }
        
        
        printf("Done Part B.)\n");
        
        // get random number seeded based on time
        // only do this once for the entire program
        srand((unsigned)time(0));
        
        /**
         part C.)
         Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer > do this until you have allocated 50 times
         - Keep track of each operation so that you eventually malloc() 50 bytes, in total
         > if you have already allocated 50 times, disregard the random and just free() on each
         iteration
         - Keep track of each operation so that you eventually free() all pointers
         > don't allow a free() if you have no pointers to free()
         */
        printf("Part C.) Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer until 50 bytes have been allocated.\n");
        
        int partCAllocated = 0;
        int partCCount = 0;
        
        void* partC[50];
        
        // rand() % 2 can equal 0 or 1 randomly
        // if 1 then allocate 1
        // if 0 then free 1
        
        while (partCCount < 50) {
            if (rand() % 2) {
                partC[partCAllocated++] = malloc(1);
                partCCount++;
            } else {
                // check to make sure that there is at least 1 allocated
                if (partCAllocated > 0) {
                    free(partC[--partCAllocated]);
                }
            }
        }
        
        // then free rest
        
        int c;
        
        for (c = 0; c < partCAllocated; c++) {
            free(partC[c]);
        }
        
        printf("Done Part C.)\n");
        
        /**
         part D.)
         Randomly choose between a randomly-sized malloc() or free()ing a pointer – do this many times (see below)
         - Keep track of each malloc so that all mallocs do not exceed your total memory capacity - Keep track of each operation so that you eventually malloc() 50 times
         - Keep track of each operation so that you eventually free() all pointers
         - Choose a random allocation size between 1 and 64 bytes
         
         */
        
        printf("Part D.) Randomly choose between a randomly-sized malloc() or free()ing a pointer.\n");
        
        void* partD[50];
        
        int partDAllocated = 0;
        int partDCount = 0;
        
        while (partDCount < 50) {
            
            if (rand() % 2) {
                // rand() % 64 + 1
                // generate a random number between 1 and 64
                void* temp = malloc(rand() % 64 + 1);
                if (temp != NULL) {
                    partD[partDAllocated++] = temp;
                    partDCount++;
                }
            } else {
                if (partDAllocated > 0) {
                    free(partD[--partDAllocated]);
                }
            }
            
        }
        
        // then free rest
        
        int d;
        
        for (d = 0; d < partDAllocated; d++) {
            free(partD[d]);
        }
        
        printf("Done Part D.)\n");
        
        /**
         part E.)
         
         */
        
        /**
         part F.)
         
         */


    
    }
    
    return 0;
}
