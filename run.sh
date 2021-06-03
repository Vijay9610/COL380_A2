#!/bin/bash
n=$1
filename=$2
t=$3
st=$4
if [[ $4 -eq 4 ]]
then
	mpiexec -n $3 ./mpi $1 $2 $3
elif [[ $4 -lt 4 ]]
then
	./crout_LU $1 $2 $3 $4
fi
