#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#define M 1000
#define N 1000
#define K 1000

double A[M][K], B[K][N], C[M][N];

int main() {
    int i, j, k;
    double start_time, end_time;
    start_time = omp_get_wtime();

   //to improve performance set num of threads to 4
   //omp_set_num_threads(4);
	
    // Initialize matrices A and B
    for (i = 0; i < M; i++) {
        for (j = 0; j < K; j++) {
            A[i][j] = (double) rand() / RAND_MAX;
        }
    }

    for (i = 0; i < K; i++) {
        for (j = 0; j < N; j++) {
            B[i][j] = (double) rand() / RAND_MAX;
        }
    }

   
    #pragma omp parallel for  private(i, j, k) shared(A, B, C) //to improve performance specify number of threads use num_threads(4)
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    end_time = omp_get_wtime();
    printf("Execution time: %f seconds\n", end_time - start_time);
   // printf("%d",omp_get_num_threads());

    return 0;
}
