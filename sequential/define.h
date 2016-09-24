#ifndef define_h
#define define_h

/***** Librarys/Headers ****/
#include <stdio.h>
#include <stdlib.h>

/**** Structs ****/
typedef struct
{
    int rows;
    int cols;
    int **m;    // 2D matrix
} Matrix;

/**** Constants ****/
// Booleans
#define FALSE               0
#define TRUE                1

// Errors
#define ARRAY_MEMORY_ERROR  10

// Random numbers
#define RANGE 4    // [0..RANGE)

/***** Function Prototypes *****/
// main.c prototypes
void test(Matrix *A, Matrix *B, Matrix *C);
void setUpMatrices(Matrix *a, Matrix *b, Matrix *c);
void printResult(Matrix *A, Matrix *B, Matrix *C, int bVal);
void freeMemory(Matrix *A, Matrix *B, Matrix *C);

// 2DArray.c prototypes
void setUp2D(Matrix *a, int numRows, int numCols, int bFillRand);
void allocate2D(Matrix *a);
void fillRandom2D(Matrix *a);
void fillZeroes2D(Matrix *a);
void print2D(Matrix *a);
void free2D(Matrix *a);

// matrix.c prototypes
int isDefined(Matrix *a, Matrix *b);
int multiply(Matrix *a, Matrix *b, Matrix *c);

#endif /* define_h */
