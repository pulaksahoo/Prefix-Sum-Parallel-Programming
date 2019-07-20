# Prefix-Sum-Parallel-Programming
The objective of this project was to find an optimized Prefix Sum and then analyse it to its corresponding sequential mode with respect to its efficiency in terms of performance. There was also an analysis on the performance  of OpenMP and OpenMPI.

There are two parallel programs (one using OpenMP and the other using MPI) to compute the prefix
sums for a large sequence X[1..N] of integers. Taking large enough values of N. I needed to report
the best way to partition the program and running them in parallel which gives the best
performance.
My code allowed easy changing of parameters like the number of threads, processors and the
input size N. For a given input size N you can generate the input sequence of integers X[1..N] by a
series of calls to a function that generates random numbers.
