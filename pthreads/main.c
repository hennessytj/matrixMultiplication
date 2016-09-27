#include "define.h"
/***********************************************************************
 * main.c written by DSU_410 team ...
 *
 * Description: Given two square matrices, perform matrix multiplication
 * and store the result. Performs matrix multiplication concurrently 
 * using pthreads.
 *
 * compile: %gcc main.c 2DArray.c -o mmpthreads -lpthread
 * execute: ./mmpthreads
 *
 * Process:
 * 1.) Fill two 2D arrays A and B with random values.
 * 2.) Multiply both arrays and store result into 2D array C.
 * 3.) Print out results if size is appropriate.
 ************************************************************************/

// Use constants so size is known at compile time for 2D global arrays
#define N 2000
#define P 2000
#define M 2000

int A[N][P];
int B[P][M];
int C[N][M];

/*******************************   multiplyMatrices  ***************************
 * int multiplyMatrices(int row)
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
void multiplyMatrices(int row)
{
    int j, k;
    for (j = 0; j < M; j++)
        for (k = 0; k < P; k++)
            C[row][j] += A[row][k] * B[k][j];
}

/* Initial conjecture for implementing openMp version
void multiplyMatrices(int row)
{
    int i, j, k;
    #pragma omp parallel for
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            for (k = 0; k < P; k++)
                C[i][j] += A[i][k] * B[k][j];
}
 */

/*********************************   partition  ********************************
 * void *partition(void *p)
 *
 * Description: Partitions matrix multiplication by dividing rows amongst
 * threads.  Every thread calls multilpyMatrices for each of its assigned
 * rows.
 *
 * Process:
 * 1.) Divide work.
 * 2.) Call multiplyMatrices.
 * 3.) Threads exit.
 *
 * Parameter     Direction   Description
 * ----------------------------------------------------------------------------
 * p             in          thread tid used for division of work amongst 
 *                           threads.
 *
 * Returns       Method      Description
 * ----------------------------------------------------------------------------
 * N/A
 *
 * NOTES:
 * - Calls multiplyMatrices N (constants defined above) times partitioned amongst
 *   threads.
 * - Since all arrays are global, the arrays are visible to all functions in
 *   this file.
 ******************************************************************************/
void *partition(void *p)
{
    int i;
    long tid = (long) p;
    int numRows = N / NUM_THREADS;
    int remainingRows = N % NUM_THREADS;
    int startRow = numRows * tid;
    int endRow;
    // last thread is one less than NUM_THREADS [0..NUM_THREADS)
    // last thread is assigned remaining number of rows, in the worst case is
    // N - 1
    if (tid == NUM_THREADS - 1)
    {
        endRow = numRows * tid + numRows + remainingRows;
    }
    else
    {
        endRow = numRows * tid + numRows;
    }
    /* Used for testing work distribution
    for (i = startRow; i < endRow; i++)
        printf("Tid %d does row %d\n", tid, i);
    */
    for (i = startRow; i < endRow; i++)
        multiplyMatrices(i);
    pthread_exit(NULL);
}

/*******************************   multiply   ********************************
 * int multiply()
 *
 * Description: Performs matrix multiplication on arrays A and B, stores
 * results into C.
 *
 * Process:
 * 1.) Create NUM_THREADS (constant in define.h) threads.
 * 2.) Send threads to partition function, aka entry point function.
 * 3.) Join all threads.
 *
 * Parameter     Direction   Description
 * ----------------------------------------------------------------------------
 * N/A
 *
 * Returns       Method      Description
 * ----------------------------------------------------------------------------
 * N/A
 * NOTES:
 * - See pthreads documentation for more specific information.
 ******************************************************************************/
void multiply()
{
    long t;
    void *status;
    pthread_t tid[NUM_THREADS];
    // Create threads and partition work
    for (t = 0; t < NUM_THREADS; t++)
         pthread_create(&tid[t], NULL, partition, (void *) t);
    // Join threads
    for (t = 0; t < NUM_THREADS; t++)
        pthread_join(tid[t], &status);
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
    if (FALSE)
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
