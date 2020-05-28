#include <thread>
#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>

typedef unsigned long long big_int;

int calcIterations(big_int n) {
	// Determines step count for Collatz sequence from n to 1
	int steps=0;
	while(n>1) {
		// check that n won't wrap around
		if(n*3+1<n) return -1;

		// if n divides by 2, divide by 2, else times by 3 and add 1
		if(n%2) {
			n=n*3+1;
		} else {
			n/=2;
		}
		++steps;
	}
	return steps;
}

void calcMaxIterations(big_int N, big_int M, 
  	// Return values 
	int &maxIterations, big_int &maxN
) {
  	// Finds the max path length for all n between N and M
  	if(M<N) return;

  	maxIterations=0;
  	maxN=0;

#ifdef OMP_ENABLED
#pragma omp parallel for schedule(dynamic)
#endif
	  for(big_int i = N; i<M; ++i) {
	    int currIterations = calcIterations(i);
	    if ( maxIterations < currIterations ) {
	      maxIterations=currIterations;
	      maxN=i;
	    }
	  }
}

void printMax(int maxIterations, big_int maxN) {
	  std::cout << "Max: " << maxIterations 
	    << " At: " << maxN 
	    << std::endl;
}

void openmp(big_int start, big_int end) {
	int maxIterations = 0;
	big_int maxN;
	auto t1 = std::chrono::high_resolution_clock::now();
	calcMaxIterations(start, end, maxIterations, maxN);
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
	std::cout << "Duration: " << duration << "\n";
	printMax(maxIterations, maxN);
}

int main(int argc, char** args) {
	big_int start = 0;
	big_int end = 0;

	start = atoll(args[1]);
	end = atoll(args[2]);	

	#ifdef OMP_ENABLED
	  openmp(start, end);
	#endif

}
