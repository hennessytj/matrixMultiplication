#include "define.h"

/***********************************************************************
 * matrix.c written by DSU_410 team ...
 *
 * Description: Performs mathematical matrix operations for 2D arrays
 * (aka Matrix structures in this implementation).
 * Sort of like an API. Works with a structure of type Matrix, which
 * contains a 2D array and values for rows/columns.
 *
 * Functions:
 * - isDefined
 * - multiply
 *
 * compile: Used with main.c, not meant to be independently executable
 *
 * Process:
 * 1.) Used when functions are invoked.
 ************************************************************************/

/*******************************   isDefined   ********************************
 * int isDefined(Matrix *a, Matrix *b)
 *
 * Description: Ensures matrix multiplication is mathematically defined.
 *
 * Process:
 * 1.) Assign values to a->rows and a->cols.
 * 2.) Call allocate2D(a)
 * 3.) Call fillRandom(a)
 *
 * Parameter     Direction   Description
 * ----------------------------------------------------------------------------
 * a             in/out      ptr to Matrix structure, see define.h.
 *                           Assigns values to a->rows and a->cols and stores
 *                           reference to dynamic 2D array.
 * numRows       in          Total number of rows in 2D array
 * numCols       in          Total number of columns in 2D array
 *
 * Returns       Description
 * ----------------------------------------------------------------------------
 * TRUE          Matrix multiplication is defined.
 * FALSE         Matrix multiplication is not defined.
 *
 * NOTES:
 * - Assumes Matrix structures were allocated properly.
 ********************************************************************************/
int isDefined(Matrix *a, Matrix *b)
{
    int bVal = TRUE;
    if (a->cols != b->rows)
        bVal = FALSE;
    return bVal;
}

/*******************************   multiply   ********************************
 * int multiply(Matrix *a, Matrix *b, Matrix *c)
 *
 * Description: Performs matrix multiplication on Matrices A and B, stores 
 * results into Matrix c.
 *
 * Process:
 * 1.) Perform multiplication and store result.
 *
 * Parameter     Direction   Description
 * ----------------------------------------------------------------------------
 * a             in          ptr to Matrix structure, see define.h.
 *                           Reads values from 2D int array within Matrix.
 * b             in          ptr to Matrix structure, see define.h.
 *                           Reads values from 2D int array within Matrix.
 * c             out         ptr to Matrix structure, see define.h.
 *                           Writes result of multiplication with matrices A
 *                           and B into C.
 * Returns       Description
 * ----------------------------------------------------------------------------
 * TRUE          Matrix multiplication was performed.
 * FALSE         Matrix multiplication was not performed.
 *
 * NOTES:
 * - Assumes Matrix structures were allocated properly.
 * - Does not perform multiplication for undefined matrices.
 ******************************************************************************/
int multiply(Matrix *a, Matrix *b, Matrix *c)
{
    int bVal = TRUE;
    int i;
    int j;
    int k;
    bVal = isDefined(a, b);
    if (bVal)
    {
        for (i = 0; i < a->rows; i++)
            for (j = 0; j < b->cols; j++)
                for (k = 0; k < b->rows; k++)
                    c->m[i][j] += a->m[i][k] * b->m[k][j];
    }
    return bVal;
}