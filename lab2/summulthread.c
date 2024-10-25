#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>  // Library for threads
#include <time.h>     // Library for measuring execution time

// Structure to store the range and result for each thread
typedef struct {
    unsigned long long start;
    unsigned long long end;
    unsigned long long result;
} ThreadData;

// Function executed by each thread to calculate a partial sum
void *partial_sum(void *arg) {
    ThreadData *data = (ThreadData *)arg;  // Cast the argument to ThreadData
    unsigned long long sum = 0;

    // Calculate the sum for the given range
    for (unsigned long long i = data->start; i <= data->end; ++i) {
        sum += i;
    }

    data->result = sum;  // Store the result in the struct
    return NULL;
}

int main(int argc, char *argv[]) {
    // Check if the user provided the correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <num_threads> <n>\n", argv[0]);
        return 1;
    }

    int numThreads = atoi(argv[1]);          // Convert input to integer
    unsigned long long n = atoll(argv[2]);   // Convert input to long long integer

    pthread_t threads[numThreads];           // Array to store thread IDs
    ThreadData threadData[numThreads];       // Array to store thread data

    unsigned long long range = n / numThreads;  // Calculate the range for each thread
    unsigned long long start = 1;               // Start of the first range

    // Start measuring time
    clock_t start_time = clock();

    // Create threads and assign each thread a range
    for (int i = 0; i < numThreads; ++i) {
        threadData[i].start = start;
        threadData[i].end = (i == numThreads - 1) ? n : start + range - 1;
        pthread_create(&threads[i], NULL, partial_sum, &threadData[i]);
        start += range;  // Move to the next range
    }

    // Wait for all threads to complete and sum their results
    unsigned long long totalSum = 0;
    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], NULL);  // Wait for thread to complete
        totalSum += threadData[i].result;  // Accumulate the result
    }

    // Stop measuring time
    clock_t end_time = clock();

    // Calculate the elapsed time in seconds
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Print the result and execution time
    printf("Sum (multi-thread) from 1 to %llu: %llu\n", n, totalSum);
    printf("Execution Time: %.6f seconds\n", elapsed_time);

    return 0;
}