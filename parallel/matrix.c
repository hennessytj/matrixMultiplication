#include "define.h"

pthread_mutex_t lock;
pthread_mutex_t destination_lock;

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

void job(void* s) {
    MatrixOperation* operation = (MatrixOperation*)s;
    Matrix* a;
    Matrix* b;

    int thread_a_current_row;
    int thread_b_current_row;
    int thread_b_current_column;

    a = operation->a;
    b = operation->b;

    int dest_column;
    int dest_row;

    int result;
//    for (i = 0; i < a->rows; i++)
//        for (j = 0; j < b->cols; j++)
//            for (k = 0; k < b->rows; k++)
//                c->m[i][j] += a->m[i][k] * b->m[k][j];
    while(1) {
        pthread_mutex_lock(&lock);
        if (a->rows == operation->a_current_row) {
            pthread_mutex_unlock(&lock);
            pthread_exit(NULL);
        }

        thread_a_current_row = operation->a_current_row;
        thread_b_current_row = operation->b_current_row;
        thread_b_current_column = operation->b_current_column;

        operation->b_current_row++;
        if (b->rows == operation->b_current_row) {
            operation->b_current_row = 0;
            operation->b_current_column++;
        }
        if (b->cols == operation->b_current_column) {
            operation->b_current_column = 0;
            operation->a_current_row++;
        }
        pthread_mutex_unlock(&lock);

        result =
                a->m[thread_a_current_row][thread_b_current_row] *
                b->m[thread_b_current_row][thread_b_current_column];

        pthread_mutex_lock(&destination_lock);
        operation->dest->m[thread_a_current_row][thread_b_current_column] += result;
        pthread_mutex_unlock(&destination_lock);
    }
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
    pthread_mutex_init(&lock, NULL);
    pthread_mutex_init(&destination_lock, NULL);

    MatrixOperation matrixOperation =
            {.a = a, .b = b, .a_current_row=0, .b_current_column=0, .b_current_row=0, .dest = c};

    int bVal = TRUE;
    int i;
    int j;
    int k;
    int tid;
    bVal = isDefined(a, b);
    if (bVal)
    {
        pthread_t* threads = (pthread_t*)calloc(sizeof(pthread_t), NUM_THREADS);
        pthread_t* cursor = threads;
        for (tid=0; tid < NUM_THREADS; tid++) {
            pthread_create(cursor, NULL, job, &matrixOperation);
            cursor++;
        }

        cursor = threads;
        void* status;
        for (tid=0; tid < NUM_THREADS; tid++) {
            pthread_join(*cursor, &status);
            cursor++;
        }
        free(threads);
    }

    pthread_mutex_destroy(&destination_lock);
    pthread_mutex_destroy(&lock);
    return bVal;
}