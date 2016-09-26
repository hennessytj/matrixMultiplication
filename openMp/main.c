#include "define.h"
/***********************************************************************
 * main.c written by DSU_410 team ...
 *
 * Description: Given two square matrices, perform matrix multiplication
 * and store the result. Performs matrix multiplication concurrently 
 * using pthreads.
 *
 * compile: %gcc main.c 2DArray.c -o mmpthreads
 * execute: ./mmpthreads
 *
 * Process:
 * 1.) Fill two 2D arrays A and B with random values.
 * 2.) Multiply both arrays and store result into 2D array C.
 * 3.) Print out results if size is appropriate.
 ************************************************************************/

// Use constants so size is known at compile time for 2D global arrays
#define N 3
#define P 3
#define M 3

int A[N][P];
int B[P][M];
int C[N][M];

/***********************************   multiply  *******************************
 * int multiplyMatrices()
 *
 * Description: Performs matrix multiplication on Matrices A and B for the given
 * row, and stores the result into array C.
 *
 * Process:
 * 1.) Perform multiplication and store result.
 *
 * Parameter     Direction   Description
 * ----------------------------------------------------------------------------
 * row           in          index of row A used in multiplication and the row
 *                           the products are stored into in array C.
 *
 * Returns       Method      Description
 * ----------------------------------------------------------------------------
 * Product       Side effect Stores the product of matrix multiplication of A
 *                           and B into C.
 *
 * NOTES:
 * - Called a total of N (constants defined above) times partitioned amongst
 *   threads.
 * - Since all arrays are global, the arrays are visible to all functions in 
 *   this file.
 ******************************************************************************/
void multiply()
{
    int i, j, k;
    #pragma omp parallel for private(i, j, k)
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            for (k = 0; k < P; k++)
                C[i][j] += A[i][k] * B[k][j];
}

/*******************************  setUpMatrices  *************************
 * void setUpMatrices()
 *
 * Description: Sets up Matrices with initial values.
 *
 * Process:
 * 1.) Call functions in 2DArray.c to assign appropriate values to initial
 *     arrays.
 *
 * Parameter     Direction   Description
 * ---------------------------------------------------------------------
 * N/A
 *
 * Returns       Method      Description
 * ---------------------------------------------------------------------
 * N/A
 * NOTES:
 * - Since all arrays are global, the arrays are visible to all functions in
 *   this file.
 * - 
 ***********************************************************************/
void setUpMatrices()
{
    int bFillRand = TRUE;
    int bDoNotFillRand = FALSE;
    // Assigns values to structure rows and cols, allocates memory
    // for 2D int array, and assigns random values to 2D array
    setUp2D(N, P, A, bFillRand);        // A is a NxP matrix, operand 1
    setUp2D(P, M, B, bFillRand);        // B is a PxM matrix, operand 2
    setUp2D(N, M, C, bDoNotFillRand);   // C is a NxM matrix, result
}

/***************************  printResult  *****************************
 * void printResult()
 *
 * Description: Prints out values of Matrices a and b then the result of
 * their matrix multiplication stored in Matrix c.
 * set up properly.
 *
 * Process:
 * 1.) Prints out Matrix a, then Matrix b, then Matrix c.
 *
 * Parameter     Direction   Description
 * ---------------------------------------------------------------------
 * N/A
 *
 * Returns       Method      Description
 * ---------------------------------------------------------------------
 * N/A
 * NOTES:
 * - Since all arrays are global, the arrays are visible to all functions in
 *   this file.
 ***********************************************************************/
void printResult()
{
    if (TRUE)
    {
        // Too big don't bother printing
        return;
    }
    printf("Matrix A\n");
    print2D(N, P, A);
    printf("Matrix B\n");
    print2D(P, M, B);
    printf("Result of Multiplication\n");
    print2D(N, M, C);
}

int main(int argc, const char * argv[])
{
    
    // Set up Matrices, includes memory allocation and assigning values
    setUpMatrices();
    
    // Try to multiply Matrices A B, store result into Matrix C
    // If multiplication not performed FALSE is returned
    multiply();
    
    // Matrix multiplication was performed, print out results stored
    // in Matrix C
    printResult();
    
    return 0;
}
