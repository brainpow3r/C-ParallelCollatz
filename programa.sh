#!/bin/sh
#SBATCH -p short
#SBATCH -N1
#SBATCH -c12
#SBATCH -C alpha 
mpirun ./with_openmp 1 999999999999
