#include <omp.h>
#include <stdio.h>

long long fib_serial(long long n) {
  if (n < 2)
    return n;
  long long i = fib_serial(n - 1);
  long long j = fib_serial(n - 2);
  return i + j;
}

int main() {
  long long n = 35;
  double tstart, tstop, tcalc;

  tstart = omp_get_wtime();
  long long result = fib_serial(n);
  tstop = omp_get_wtime();
  tcalc = tstop - tstart;

  printf("fib(%lld) = %lld\n", n, result);
  printf("Time taken (serial): %f seconds\n", tcalc);

  return 0;
}
