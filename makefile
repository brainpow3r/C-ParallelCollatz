CC=g++
CFLAGS=--std=c++11
EXES=with_openmp

all: $(EXES)

with_openmp: collatz.cpp
	$(CC) $(CFLAGS) -DOMP_ENABLED -o $@ $< -fopenmp
	
clean:
	rm $(EXES)
