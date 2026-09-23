#include <omp.h>
#include <stdio.h>

int fib(int n) {
  int i, j;
  if (n < 2)
    return n;

  #pragma omp task shared(i)
  i = fib(n - 1);

  #pragma omp task shared(j)
  j = fib(n - 2);

  #pragma omp taskwait
  return i + j;
}

int main() {
  int n = 35;
  int result;
  double tstart, tstop, tcalc;

  tstart = omp_get_wtime();

  #pragma omp parallel
  {
    #pragma omp single
    {
      result = fib(n);
    }
  }

  tstop = omp_get_wtime();
  tcalc = tstop - tstart;

  printf("fib(%d) = %d\n", n, result);
  printf("Time taken (parallel): %f seconds\n", tcalc);

  return 0;
}
