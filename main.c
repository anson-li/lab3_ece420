/*
   Remember to change the exit value of the wrong case to -1 !!!
   Test the result stored in the "data_output" by a serial version of calculation

   -----
   Compiling:
    "Lab3IO.c" should be included and "-lm" tag is needed, like
    > gcc serialtester.c Lab3IO.c -o serialtester -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "timer.h"
#include "Lab3IO.h"

#define TOL 0.0005

int main(int argc, char* argv[])
{
        int i, j, k, size;
        double** Au;
        double* X;
        double temp, error, Xnorm;
        double start, end, elapsed;
        int* index;
        FILE* fp;
        int thread_count = atoi(argv[1]);

        /*Load the datasize and verify it*/
        Lab3LoadInput(&Au, &size);
        /*Calculate the solution by serial code*/
        X = CreateVec(size);
        index = malloc(size * sizeof(int));
        for (i = 0; i < size; ++i) {
            index[i] = i;
        }

        GET_TIME(start);
        if (size == 1)
                X[0] = Au[0][1] / Au[0][0];
        else{
            /*Gaussian elimination*/
            // this is a section
            # pragma omp parallel num_threads(thread_count) \
            default(none) shared(X, Au, size, index) private(i, k, j, temp)

                #pragma omp for ordered
                for (k = 0; k < size - 1; ++k) {
                        /*Pivoting*/
                        // Add section here
                        temp = 0;
                        for (i = k, j = 0; i < size; ++i) {
                                if (temp < Au[index[i]][k] * Au[index[i]][k]) {
                                        temp = Au[index[i]][k] * Au[index[i]][k];
                                        j = i;
                                }
                        }

                        if (j != k) /*swap*/ {
                                i = index[j];
                                index[j] = index[k];
                                index[k] = i;
                        }
                        // Add section here
                        /*calculating*/
                        // #pragma omp for collapse(2)
                        for (i = k + 1; i < size; ++i) {
                                for (j = k; j < size + 1; ++j)
                                        temp = Au[index[i]][k] / Au[index[k]][k];
                                        Au[index[i]][j] -= Au[index[k]][j] * temp;
                        }
                }
                // this is a section
                /*Jordan elimination*/

                # pragma omp for collapse(2)
                for (k = size - 1; k > 0; --k) {
                        for (i = k - 1; i >= 0; --i ) {
                                temp = Au[index[i]][k] / Au[index[k]][k];
                                Au[index[i]][k] -= temp * Au[index[k]][k];
                                Au[index[i]][size] -= temp * Au[index[k]][size];
                        }
                }

                /*solution*/
                # pragma omp for
                for (k=0; k< size; ++k)
                        X[k] = Au[index[k]][size] / Au[index[k]][k];
        }
        GET_TIME(end);
        printf("Time elapsed: %f seconds. \n", end - start);
        Lab3SaveOutput(X, size, end - start);

        DestroyVec(X);
        DestroyMat(Au, size);
        free(index);
        return 0;
}
