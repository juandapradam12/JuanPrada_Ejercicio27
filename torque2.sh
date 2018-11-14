#!/bin/bash


module load mpich/3.2.1

mpicc sample.c -o sample -lm

mpiexec -n 4 ./sample 1000 2.5 3.5

python plots.py 

