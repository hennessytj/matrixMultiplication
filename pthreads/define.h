#ifndef define_h
#define define_h

/***** Librarys/Headers ****/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/**** Constants ****/
// Booleans
#define FALSE   0
#define TRUE    1

// Threads
#define NUM_THREADS     5

// Random numbers
#define RANGE 5    // [0..RANGE)

/***** Function Prototypes *****/
// 2DArray.c prototypes
void setUp2D(int rows, int cols, int a[][cols], int bFillRand);
void fillRandom2D(int rows, int cols, int a[][cols]);
void fillZeroes2D(int rows, int cols, int a[][cols]);
void print2D(int rows, int cols, int a[][cols]);

#endif /* define_h */
