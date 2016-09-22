#include "define.h"

/***********************************************************************
 * 2DArray.c written by DSU_410 team ...
 *
 * Description: Performs routine operations for 2D arrays sort of like
 * an API. Works with a structure of type matrix, which contains a 2D
 * array.
 *
 * Functions:
 * - setUp2D
 * - allocate2D
 * - fill2DRandom2D
 * - print2D
 * - free2D
 *
 * compile: Used with main.c, not meant to be independently executable
 *
 * Process:
 * 1.) Used when functions are invoked.
 ************************************************************************/

/*****************************   setUp2D   ******************************
 * void setUp2D(Matrix *a, int numRows, int numCols)
 *
 * Description: Assigns values to Matrix structure, allocates memory
 * for it, and assigns random values to it.
 *
 * Process:
 * 1.) Assign values to a->rows and a->cols.
 * 2.) Call allocate2D(a)
 * 3.) Call fillRandom(a)
 *
 * Parameter     Direction   Description
 * ---------------------------------------------------------------------
 * a             in/out      ptr to Matrix structure, see define.h.
 *                           Assigns values to a->rows and a->cols and stores
 *                           reference to dynamic 2D array.
 * numRows       in          Total number of rows in 2D array
 * numCols       in          Total number of columns in 2D array
 *
 * NOTES:
 * - Assumes numRows and numCols are accurate and viable.
 * - Failure of memory allocation aborts program.
 ***********************************************************************/
void setUp2D(Matrix *a, int numRows, int numCols, int bFillRand)
{
    a->rows = numRows;
    a->cols = numCols;
    allocate2D(a);
    if (bFillRand)
    {
        fillRandom2D(a);
    }
    else
    {
        fillZeroes2D(a);
    }
}

/*****************************  allocate2D  *****************************
 * void allocate2D(Matrix *a)
 *
 * Description: Dynamically allocates memory for Matrix structure's 2D
 * array in.  
 *
 * Process:
 * 1.) Allocate memory for array of pointers.
 * 2.) Allocate memory for every of integers, pointed to by above.
 *
 * Parameter     Direction   Description
 * ---------------------------------------------------------------------
 * a             in/out      ptr to Matrix structure, see define.h. Stores
 *                           references to allocated memory into a.
 *
 * NOTES:
 * - Assumes values of a->rows and a->cols are accurate and viable.
 * - Aborts program if memory allocation fails.
 ***********************************************************************/
void allocate2D(Matrix *a)
{
    int i;
    // Allocate memory for array of pointers
    a->m = malloc(sizeof(int *) * (a->rows));
    if (a->m == NULL)
    {
        printf("Error: no memory for array\n");
        exit(ARRAY_MEMORY_ERROR);
    }
    // Allocate memory for each array of integers pointed to by
    // array of pointers from above
    for (i = 0; i < a->rows; i++)
    {
        a->m[i] = malloc(sizeof(int) * (a->cols));
        if (a->m[i] == NULL)
        {
            printf("Error: no memory for array\n");
            exit(ARRAY_MEMORY_ERROR);
        }
    }
}

/*****************************  fillRandom2D  *****************************
 * void fillRandom2D(Matrix *a)
 *
 * Description: Takes Matrix structure and fills it with random values
 * less than RANGE (constant defined in define.h).
 *
 * Process:
 * 1.) For each column in every row, assign random values.
 *
 * Parameter     Direction   Description
 * ---------------------------------------------------------------------
 * a             out         ptr to Matrix structure, see define.h. Writes
 *                           random values into array.
 *
 * NOTES:
 * - Assumes matrix has been allocated and values of a->rows and a->cols 
 *   are accurate and viable.
 ***********************************************************************/
void fillRandom2D(Matrix *a)
{
    int i;
    int j;
    for (i = 0; i < a->rows; i++)
        for (j = 0; j < a->cols; j++)
            a->m[i][j] = rand() % RANGE;
}

/*****************************  fillZeroes2D  *****************************
 * void fillZeroes2D(Matrix *a)
 *
 * Description: Takes Matrix structure and fills it with 0s.
 *
 * Process:
 * 1.) For each cell, assign 0.
 *
 * Parameter     Direction   Description
 * ---------------------------------------------------------------------
 * a             out         ptr to Matrix structure, see define.h. Writes
 *                           0s into array.
 *
 * NOTES:
 * - Assumes matrix has been allocated and values of a->rows and a->cols
 *   are accurate and viable.
 ***********************************************************************/
void fillZeroes2D(Matrix *a)
{
    int i;
    int j;
    for (i = 0; i < a->rows; i++)
        for (j = 0; j < a->cols; j++)
            a->m[i][j] = 0;
}

/****************************  print2D  ********************************
 * void print2D(Matrix *a)
 *
 * Description: Used for printing out Matrix structure values.
 *
 * Process:
 * 1.) Standard 2D array printing function, nothing special.
 *
 * Parameter     Direction   Description
 * ---------------------------------------------------------------------
 * a             in             ptr to Matrix structure, see define.h.
 *                              Reads values and prints to stdout.
 *
 * NOTES:
 * - Assumes matrix has been allocated and values of a->rows and a->cols
 *   are accurate and viable.
 ***********************************************************************/
void print2D(Matrix *a)
{
    int i;
    int j;
    if (a->rows > 8)
    {
        // Too big don't bother printing
        return;
    }
    printf("\n");
    for (i = 0; i < a->rows; i++)
    {
        for (j = 0; j < a->cols; j++)
        {
            printf("%-6d", a->m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/****************************   free2D   ********************************
 * void free2D(Matrix *a)
 *
 * Description: Frees dynamically allocated memory for matrix structure.
 * Frees the 2D array within matrix.
 *
 * Process:
 * 1.) Free each array pointed to by a->m
 * 2.) Free array of pointers a->m
 *
 * Parameter     Direction   Description
 * ---------------------------------------------------------------------
 * a             in/out      Matrix structure, see define.h. Dynamic
 *                           memory is freed.
 *
 * NOTES:
 * - Assumes matrix has been allocated and values of a->rows and a->cols
 *   are accurate and viable.
 ***********************************************************************/
void free2D(Matrix *a)
{
    int i;
    for (i = 0; i < a->rows; i++)
        free(a->m[i]);   // frees each array pointed at by a->m
    free(a->m);          // frees a->m, array of pointers
}