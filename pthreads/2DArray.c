#include "define.h"

/***********************************************************************
 * 2DArray.c written by DSU_410 team ...
 *
 * Description: Performs routine operations for 2D arrays, sort of like
 * an API.
 *
 * Functions:
 * - setUp2D
 * - allocate2D
 * - fill2DRandom2D
 * - print2D
 *
 * compile: Used with main.c, not meant to be independently executable.
 *
 * Process:
 * 1.) Used when functions are invoked.
 ************************************************************************/

/*****************************   setUp2D   ******************************
 * void setUp2D(int rows, int cols, int a[][cols], int bFillRand)
 *
 * Description: Wrapper function for assigning values to 2D array. Either
 * calls function to fill 2D array with random values, or calls function
 * to assign all 0 values.
 *
 * Process:
 * 1.) If bFillRand is true, invoke fillRandom2D, otherwise fillZeroes2D.
 *
 * Parameter     Direction   Description
 * ---------------------------------------------------------------------
 * rows          in          total number of rows
 * cols          in          total number of columns
 * a             out         2D array that is assigned values
 * bFillRand     in          boolean value used to determine what
 *                           function to call for assigning values.
 *
 * NOTES:
 * N/A
 ***********************************************************************/
void setUp2D(int rows, int cols, int a[][cols], int bFillRand)
{
    if (bFillRand)
    {
        fillRandom2D(rows, cols, a);
    }
    else
    {
        fillZeroes2D(rows, cols, a);
    }
}


/*****************************  fillRandom2D  *****************************
 * void fillRandom2D(int rows, int cols, int a[][cols])
 *
 * Description: Takes a 2D array and fills it with random values
 * less than RANGE (constant defined in define.h).
 *
 * Process:
 * 1.) For each column in every row, assign random values.
 *
 * Parameter     Direction   Description
 * -----------------------------------------------------------------------
 * rows          in          total number of rows
 * cols          in          total number of columns
 * a             out         ptr to Matrix structure, see define.h. Writes
 *                           random values into array.
 *
 * NOTES:
 * N/A
 ***********************************************************************/
void fillRandom2D(int rows, int cols, int a[][cols])
{
    int i;
    int j;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            a[i][j] = rand() % RANGE;
}

/*****************************  fillZeroes2D  *****************************
 * void fillZeroes2D(int rows, int cols, int a[][cols])
 *
 * Description: Takes a 2D array and fills it with 0s.
 *
 * Process:
 * 1.) For each cell, assign 0.
 *
 * Parameter     Direction   Description
 * -----------------------------------------------------------------------
 * rows          in          total number of rows
 * cols          in          total number of columns
 * a             out         ptr to Matrix structure, see define.h. Writes
 *                           0s into array.
 *
 * NOTES:
 * N/A
 ***********************************************************************/
void fillZeroes2D(int rows, int cols, int a[][cols])
{
    int i;
    int j;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            a[i][j] = 0;
}

/****************************  print2D  ********************************
 * void print2D(int rows, int cols, int a[][cols])
 *
 * Description: Used for printing 2D array values.
 *
 * Process:
 * 1.) Standard 2D array printing function, nothing special.
 *
 * Parameter     Direction   Description
 * ---------------------------------------------------------------------
 * rows          in          total number of rows
 * cols          in          total number of columns
 * a             out         2D array that is printed
 *
 * NOTES:
 * N/A
 ***********************************************************************/
void print2D(int rows, int cols, int a[][cols])
{
    int i;
    int j;
    printf("\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%-6d", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}