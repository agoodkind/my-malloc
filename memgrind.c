//
//  memgrind.c - mymalloc tester filer
//  Rutgers CS 01:198:214 Systems Programming
//  Professor John-Austen Francisco
//  Authors: Anthony Siluk & Alexander Goodkind
//  Due: 10/15/2019
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "mymalloc.h"

/**
 calculate the arithmetic mean (average) of a given array
 */
double averageTime(unsigned long long times[]) {
    int i;
    unsigned long long sumOfTimes = 0;
    for (i = 0; i < 100; i++) {
        sumOfTimes += times[i];
    }
    return (double)(sumOfTimes) / (double)100.0;
}

int main(int argc, const char *argv[]) {
#if DEBUG

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

    struct timespec testStart, testEnd, testStart1, testEnd1;

    clock_gettime(CLOCK_MONOTONIC, &testStart);
    sleep(1);
    clock_gettime(CLOCK_MONOTONIC, &testEnd);

    clock_gettime(CLOCK_REALTIME, &testStart1);
    sleep(1);
    clock_gettime(CLOCK_REALTIME, &testEnd1);

    printf("%ld, %ld, %ld, %ld, %ld, %ld\n", testStart.tv_nsec, testEnd.tv_nsec, testEnd.tv_nsec - testStart.tv_nsec, testStart.tv_sec, testEnd.tv_sec, testEnd.tv_sec - testStart.tv_sec);
    printf("%ld, %ld, %ld, %ld, %ld, %ld\n", testStart1.tv_nsec, testEnd1.tv_nsec, testEnd1.tv_nsec - testStart1.tv_nsec, testStart1.tv_sec, testEnd1.tv_sec, testEnd1.tv_sec - testStart1.tv_sec);

#endif

    int workload;
    unsigned long long timesA[100];
    unsigned long long timesB[100];
    unsigned long long timesC[100];
    unsigned long long timesD[100];
    unsigned long long timesE[100];
    unsigned long long timesF[100];

    /**
            part A.)
            malloc() 1 byte and immediately free it - do this 150 times
            */
    printf("Part A.) Malloc and freeing 1 byte, 150 times.\n...\n");
    for (workload = 0; workload < 100; workload++) {
        struct timespec start, end;

        int a;
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (a = 0; a < 150; a++) {
            void *ptr = malloc(1);
            free(ptr);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        timesA[workload] = end.tv_nsec - start.tv_nsec;
    }
    printf("Done Part A.)\n");

    /**
     part B.)
     malloc() 1 byte, store the pointer in an array - do this 150 times.
     Once you've malloc()ed 50 byte chunks, then free() the 50 1 byte pointers one by one.
     */
    printf("Part B.) Malloc 1 byte, store the pointer in an array, 150 times.\nAfter 50 times, free 50 1 by 1.\n...\n");

    for (workload = 0; workload < 100; workload++) {
        struct timespec start, end;

        int b;
        void *partB[50];
        int partBCounter = 0;
        clock_gettime(CLOCK_MONOTONIC, &start);
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
        clock_gettime(CLOCK_MONOTONIC, &end);

        timesB[workload] = end.tv_nsec - start.tv_nsec;
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
    printf("Part C.) Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer until 50 bytes have been allocated.\n...\n");

    for (workload = 0; workload < 100; workload++) {
        struct timespec start, end;

        int partCAllocated = 0;
        int partCCount = 0;

        void *partC[50];

        // rand() % 2 can equal 0 or 1 randomly
        // if 1 then allocate 1
        // if 0 then free 1
        clock_gettime(CLOCK_MONOTONIC, &start);
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
        clock_gettime(CLOCK_MONOTONIC, &end);
        timesC[workload] = end.tv_nsec - start.tv_nsec;
    }
    printf("Done Part C.)\n");

    /**
     part D.)
     Randomly choose between a randomly-sized malloc() or free()ing a pointer – do this many times (see below)
     - Keep track of each malloc so that all mallocs do not exceed your total memory capacity - Keep track of each operation so that you eventually malloc() 50 times
     - Keep track of each operation so that you eventually free() all pointers
     - Choose a random allocation size between 1 and 64 bytes
     */
    printf("Part D.) Randomly choose between a randomly-sized malloc() or free()ing a pointer.\n...\n");
    for (workload = 0; workload < 100; workload++) {
        struct timespec start, end;

        void *partD[50];

        int partDAllocated = 0;
        int partDCount = 0;
        clock_gettime(CLOCK_MONOTONIC, &start);
        while (partDCount < 50) {
            if (rand() % 2) {
                // rand() % 64 + 1
                // generate a random number between 1 and 64
                void *temp = malloc(rand() % 64 + 1);
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
        clock_gettime(CLOCK_MONOTONIC, &end);
        timesD[workload] = end.tv_nsec - start.tv_nsec;
    }
    printf("Done Part D.)\n");

    /**
     part E.)
     saturate the heap with 1 byte allocations, then free it completely
     */
    printf("Part E.) Saturate the heap with 1 byte allocations, then free it completely.\n...\n");
    for (workload = 0; workload < 100; workload++) {
        struct timespec start, end;

        clock_gettime(CLOCK_MONOTONIC, &start);

        int i;

        //instantiate an array which accounts for metadata overhead
#define PARTE_ARR_SIZE 406
        void *arrayE[PARTE_ARR_SIZE];

        //malloc until we saturate memory
        for (i = 0; i < PARTE_ARR_SIZE; i++) {
            arrayE[i] = malloc(1);
        }
        //free everything
        for (i = 0; i < PARTE_ARR_SIZE; i++) {
            free(arrayE[i]);
        }

        clock_gettime(CLOCK_MONOTONIC, &end);
        timesE[workload] = end.tv_nsec - start.tv_nsec;
    }
    printf("Done Part E.)\n");

    /**
     part F.)
    saturate the heap then free 64 bytes, followed by allocating a random byte sized between 1 and 64 and immediately freeing it
     */
    printf("Part F.) Saturate the heap with 1 byte allocations, then allocate a random byte sized between 1 and 64 and immediately freeing it.\n...\n");
    for (workload = 0; workload < 100; workload++) {
        struct timespec start, end;

        clock_gettime(CLOCK_MONOTONIC, &start);

        int i;
        //instantiate array that accounts for metadata overhead
#define PARTF_ARR_SIZE 406
        void *arrayF[PARTF_ARR_SIZE];
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        //saturate memory
        for (i = 0; i < PARTF_ARR_SIZE; i++) {
            arrayF[i] = malloc(1);
        }
        
        //free 64 bytes of memory
        for (i = 0; i < 64; i++) {
            free(arrayF[i]);
        }
        //malloc a pointer of a random size from 1 to 64 and immediately free it
        for (i = 0; i < 50; i++) {
            void *temp = malloc(rand() % 64 + 1);
            free(temp);
        }
        
        //free rest of memory
        for (i = 64; i < PARTF_ARR_SIZE; i++) {
            free(arrayF[i]);
        }

        clock_gettime(CLOCK_MONOTONIC, &end);
        timesF[workload] = end.tv_nsec - start.tv_nsec;
    }
    printf("Done Part F.)\n");
    
    /**
     print averages:
     */
    printf("Average run time for A = %g ns\n", averageTime(timesA));
    printf("Average run time for B = %g ns\n", averageTime(timesB));
    printf("Average run time for C = %g ns\n", averageTime(timesC));
    printf("Average run time for D = %g ns\n", averageTime(timesD));
    printf("Average run time for E = %0.f ns\n", averageTime(timesE));
    printf("Average run time for F = %0.f ns\n", averageTime(timesF));

    return 0;
}
