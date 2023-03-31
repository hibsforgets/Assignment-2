#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define M 1000
#define K 1000
#define N 1000
#define num 3
int *A, *B, *C;
pthread_mutex_t lock;

void *matrix_multiplication(void *arg) {
    int *id = (int*)arg;
    int start = (*id * M) / num;
    int end = ((*id) + 1) * M / num;

    for(int i = start; i < end; i++) {
        for(int j = 0; j < N; j++) {
            int sum = 0;
            for(int k = 0; k < K; k++) {
                sum += A[i * K + k] * B[k * N + j];
            }
            pthread_mutex_lock(&lock);
            C[i * N + j] += sum;
            pthread_mutex_unlock(&lock);
        }
    }
    pthread_exit(NULL);
}

int main() {
    A = calloc(M * K, sizeof(int));
    B = calloc(K * N, sizeof(int));
    C = calloc(M * N, sizeof(int));
    
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < K; j++) {
            A[i * K + j] = i + j;
        }
    }
    
    for(int i = 0; i < K; i++) {
        for(int j = 0; j < N; j++) {
            B[i * N + j] = i * j;
        }
    }

    pthread_t threads[num];
    int thread_ids[num];
    
    clock_t start_time = clock();
    
    for(int i = 0; i < num; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, matrix_multiplication, &thread_ids[i]);
    }
    
    for(int i = 0; i < num; i++) {
        pthread_join(threads[i], NULL);
    }
    
    clock_t end_time = clock();
   /*
    
    printf("\nMatrix C:\N");
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            printf("%d ", C[i * N + j]);
        }
        printf("\N");
    }
    */
    printf("\nExecution time: %f seconds\N", (double)(end_time - start_time) / CLOCKS_PER_SEC);
}
