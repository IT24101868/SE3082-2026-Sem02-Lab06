#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000
#define STRIP_SIZE 8   // matches typical SIMD width (8 doubles fit in a 256-bit AVX register)

int main() {
    double *A = malloc(N * sizeof(double));
    double *B = malloc(N * sizeof(double));
    double *C = malloc(N * sizeof(double));

    // Initialize A and B with some values
    for (int i = 0; i < N; i++) {
        A[i] = i * 1.0;
        B[i] = (i + 1) * 1.0;
    }

    double tstart, tstop, tcalc;
    tstart = omp_get_wtime();

    #pragma omp parallel for schedule(static)
    for (int strip_start = 0; strip_start < N; strip_start += STRIP_SIZE) {
        int strip_end = strip_start + STRIP_SIZE;
        if (strip_end > N) strip_end = N;   // handle the last, possibly-smaller strip

        for (int i = strip_start; i < strip_end; i++) {
            C[i] = A[i] * B[i];
        }
    }

    tstop = omp_get_wtime();
    tcalc = tstop - tstart;

    printf("Sample check: C[0] = %f, C[999999] = %f\n", C[0], C[N-1]);
    printf("Time taken (parallel, strip mining): %f seconds\n", tcalc);

    free(A);
    free(B);
    free(C);
    return 0;
}
