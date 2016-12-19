
#include <iostream> // Input and output
#include <fstream>  // File output
#include <iomanip>
#include <cstdlib>  // Standard library
#include <time.h>	// Used for randomness initialisation
#include "tstar_algo.h" // Custom made sorting algorithm
//#include <algorithm> // Used for inbuilt sorting algorithm
#include <chrono>
using namespace std; 

int main(int argc, char *argv[]) {
	
	
	
	srand (time(NULL));
	
	ofstream myfile;
	
    myfile.open ("OutputTable2.csv");
	myfile << "Here are the times for the algorithm run times.\n";
	myfile.precision(10);
	int arraylength;
	static uint64_t Arrays[16801];
			
	static uint64_t Arrays2[16801];
	


	//int arraylength = 10000; 
	
	//Arraylength when solving for 30 seconds of quicksort runtime
	//arraylength = 86835000;
	//Arraylength when solving for 30 seconds of insertionsort runtime
	arraylength = 16801;
	
	uint64_t c1;
	//RAND_MAX = arraylength;
	
	for (int i = 0; i< arraylength; i++){
		c1 = rand() % arraylength;
		Arrays[i] = c1;
		Arrays2[i] = c1;
	}
	
	//For printing the array out before
	//for (int i = 0; i < arraylength; i++) cout << Arrays[i]<<endl;
	//clock_t begin = clock();
	auto begin = std::chrono::high_resolution_clock::now();

	
	auto end = std::chrono::high_resolution_clock::now();
	//clock_t end = clock();
	//double elapsed_secs1 = double(end - begin) / CLOCKS_PER_SEC;
	//cout << "Time taken to sort with insertion:" << elapsed_secs << endl;
	myfile << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()<<",";
	
	begin = std::chrono::high_resolution_clock::now();
	
	end = std::chrono::high_resolution_clock::now();
	
	
	//double elapsed_secs2 = double(end - begin) / CLOCKS_PER_SEC;
	//myfile << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()<< endl;
	//cout << "Time taken to sort with C++ quicksort:" << elapsed_secs << endl;
	
	
	
    //myfile << "This is the first cell in the first column.\n";
	myfile.close();
	
	//cout << "ArrayOutput is:" << endl;
	//for (int i = 0; i < arraylength; i++) cout << Arrays[i]<<endl;
	
	
	return EXIT_SUCCESS;
}
