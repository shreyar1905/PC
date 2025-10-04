#include <stdio.h>
#include <math.h>
#include <omp.h>

// Function to check if a number is prime
int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    int serial_count = 0, parallel_count = 0;
    double start, end;

    // Serial version
    start = omp_get_wtime();
    for (int i = 1; i <= n; i++) {
        if (is_prime(i))
            serial_count++;
    }
    end = omp_get_wtime();
    double serial_time = end - start;

    // Parallel version
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+:parallel_count) schedule(dynamic)
    for (int i = 1; i <= n; i++) {
        if (is_prime(i))
            parallel_count++;
    }
    end = omp_get_wtime();
    double parallel_time = end - start;

    printf("\nSerial Count of primes = %d", serial_count);
    printf("\nParallel Count of primes = %d", parallel_count);
    printf("\nExecution time (serial): %f seconds", serial_time);
    printf("\nExecution time (parallel): %f seconds\n", parallel_time);

    return 0;
}
