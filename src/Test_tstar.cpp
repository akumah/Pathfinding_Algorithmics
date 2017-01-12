
#include <iostream> // Input and output
#include <fstream>  // File output
#include <iomanip>
#include <cstdlib>  // Standard library
#include <time.h>	// Used for randomness initialisation
#include <chrono>
#include "tstar_algo.hpp"
using namespace std;

int main(int argc, char *argv[]) {



	srand (time(NULL));

	ofstream myfile;

    myfile.open ("OutputTable2.csv");
	myfile << "Here are the times for the algorithm run times.\n";
	myfile.precision(10);


	auto begin = std::chrono::high_resolution_clock::now();

	vector<Point2D> result;
	Point2D initpoint = {2,6};
	Point2D endpoint = {12,7};


	SimpleMesh mesh(15, 15);
	mesh.addObstacle({3, 3}, {8, 5});  // Implicit constructor of Point2D in arguments.

	//mesh.removeObstacle(Point2D(4, 	5), Point2D(5, 4));
	mesh.addObstacle({8, 8}, {2, 2});  // Implicit constructor of Point2D in arguments.

	printMesh(mesh);
	cout << endl;
	result = tstar_mainLoop(mesh, initpoint,endpoint);
	result = astar_mainLoop(mesh, initpoint,endpoint);

	auto end = std::chrono::high_resolution_clock::now();
	myfile << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()<<",";

	begin = std::chrono::high_resolution_clock::now();

	end = std::chrono::high_resolution_clock::now();

	myfile.close();


	return EXIT_SUCCESS;
}
