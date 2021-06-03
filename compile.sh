#!/bin/bash
gcc -o crout_LU -fopenmp crout_LU.c
mpicc -g -Wall -o mpi mpi.c