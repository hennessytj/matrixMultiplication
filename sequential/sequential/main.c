#include "define.h"
/***********************************************************************
 * main.c written by DSU_410 team ...
 *
 * Description: Given two square matrices, perform matrix multiplication
 * and store the result. This is the first of three versions. It is
 * the sequential version. The next two will be concurrent versions
 * using slightly different parallel approaches.
 *
 * compile: %gcc main.c 2DArray.c matrix.c -o mmseq
 * execute: ./mmseq
 *
 * Process:
 * 1.) Fill two 2D arrays matrixA and matrixB with random values.
 * 2.) Multiply both arrays and store result into matrixC.
 *
 * Can finally check off dynamically allocating 2D arrays in C from
 * bucket list!
 ************************************************************************/
static int N = 2;
static int P = 2;
static int M = 2;

int main(int argc, const char * argv[])
{
    Matrix A, B, C;
    int bPerformed = TRUE;
    
    // Set up Matrices, includes memory allocation and assigning
    // values
    setUpMatrices(&A, &B, &C);

    // Try to multiply Matrices A B, store result into Matrix C
    // If not performed FALSE is returned
    bPerformed = multiply(&A, &B, &C);
    
    // Matrix multiplication was performed, print out results stored
    // in Matrix C
    printResult(&A, &B, &C, bPerformed);
    
    // Free memory
    freeMemory(&A, &B, &C);
    
    return 0;
}

/*******************************  test  *******************************
 * void test(Matrix *a, Matrix *b, Matrix *c)
 *
 * Description: Prints out Matrices a, b, and c to ensure they were
 * set up properly.
 *
 * Process:
 * 1.) Prints out rows and cols, then calls print2D to display
 * random values in 2D int array inside Matrix structure.
 *
 * Parameter     Direction   Description
 * ---------------------------------------------------------------------
 * a             in          ptr to Matrix structure, see define.h.
 *                           Reads values from 2D int array within Matrix.
 * b             in          ptr to Matrix structure, see define.h.
 *                           Reads values from 2D int array within Matrix.
 * c             in          ptr to Matrix structure, see define.h.
 *                           Reads values from 2D int array within Matrix.
 *
 * NOTES:
 * - Assumes values of a->rows and a->cols are accurate and viable.
 * - Assumes Matrices were properly set up and allocated.
 ***********************************************************************/
void test(Matrix *a, Matrix *b, Matrix *c)
{
    printf("A is a %d-by-%d matrix\n", a->rows, a->cols);
    print2D(a);
    printf("B is a %d-by-%d matrix\n", b->rows, b->cols);
    print2D(b);
    printf("C is a %d-by-%d matrix\n", c->rows, c->cols);
    print2D(c);
}

/*******************************  setUpMatrices  *************************
 * void setUpMatrices(Matrix *a, Matrix *b, Matrix *c)
 *
 * Description: Sets up Matrices with memory and initial values.
 *
 * Process:
 * 1.) Sets up Matrix a with memory and random values by calling setUp2D
 * 2.) Sets up Matrix b with memory and random values by calling setUp2D
 * 3.) Sets up Matrix c with memory and 0s by calling setUp2D
 *
 * Parameter     Direction   Description
 * ---------------------------------------------------------------------
 * a             out         ptr to Matrix structure, see define.h.
 *                           Writes values into 2D int array within Matrix.
 * b             out         ptr to Matrix structure, see define.h.
 *                           Writes values into 2D int array within Matrix.
 * c             out         ptr to Matrix structure, see define.h.
 *                           Writes values into 2D int array within Matrix.
 *
 * NOTES:
 * - Assumes values of a->rows and a->cols are accurate and viable.
 * - Assumes Matrices were properly set up and allocated.
 ***********************************************************************/
void setUpMatrices(Matrix *a, Matrix *b, Matrix *c)
{
    int bFillRand = TRUE;
    int bDoNotFillRand = FALSE;
    // Assigns values to structure rows and cols, allocates memory
    // for 2D int array, and assigns random values to 2D array
    setUp2D(a, N, P, bFillRand);        // A is a NxP matrix, operand 1
    setUp2D(b, P, M, bFillRand);        // B is a PxM matrix, operand 2
    setUp2D(c, N, M, bDoNotFillRand);   // C is a NxM matrix, result
}

/***************************  printResult  *****************************
 * void printResult(Matrix *a, Matrix *b, Matrix *c, int bVal)
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
 * a             in          ptr to Matrix structure, see define.h.
 *                           Reads values from 2D int array within Matrix.
 * b             in          ptr to Matrix structure, see define.h.
 *                           Reads values from 2D int array within Matrix.
 * c             in          ptr to Matrix structure, see define.h.
 *                           Reads values from 2D int array within Matrix.
 * bVal          in          Boolean value. If true multiplication was 
 *                           performed and results can be printed.
 *
 * NOTES:
 * - Assumes values of a->rows and a->cols are accurate and viable.
 * - Assumes Matrices were properly set up and allocated.
 ***********************************************************************/
void printResult(Matrix *a, Matrix *b, Matrix *c, int bVal)
{
    if (bVal)
    {
        printf("Matrix A\n");
        print2D(a);
        printf("Matrix B\n");
        print2D(b);
        printf("Result of Multiplication\n");
        print2D(c);
    }
    else
        printf("Multiplication not performed\n");
}

/***************************  freeMemory  *****************************
 * void freeMemory(Matrix *a, Matrix *b, Matrix *c)
 *
 * Description: Frees dynamically allocated memory for each Matrix
 * structure used.
 *
 * Process:
 * 1.) Frees Matrix a by calling free2D
 * 2.) Fress Matrix b by calling free2D
 * 3.) Frees Matrix c by calling free2D
 *
 * Parameter     Direction   Description
 * ---------------------------------------------------------------------
 * a             in          ptr to Matrix structure, see define.h.
 * b             in          ptr to Matrix structure, see define.h.
 * c             in          ptr to Matrix structure, see define.h.
 *
 * NOTES:
 * - Assumes values of a->rows and a->cols are accurate and viable.
 * - Assumes Matrices were properly set up and allocated.
 ***********************************************************************/
void freeMemory(Matrix *a, Matrix *b, Matrix *c)
{
    free2D(a);
    free2D(b);
    free2D(c);
}
