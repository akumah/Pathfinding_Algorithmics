
#include <iostream> // Input and output
#include <fstream>  // File output
#include <iomanip>
#include <cstdlib>  // Standard library
#include <time.h>	// Used for randomness initialisation
#include <chrono>
#include "tstar_algo_jump.hpp"
using namespace std;

int main(int argc, char *argv[]) {



	srand (time(NULL));

	ofstream myfile;

    myfile.open (argv[1]);

    //myfile.open ("OutputTable.csv");
	myfile << "Here are the times for the algorithm run times.\n";
	myfile.precision(10);



	vector<Point2D> result;

	/*

	cout << endl;
	Point2D initpoint = {2,6};
	Point2D endpoint = {12,8};


	JumpMesh mesh(15,15);
	mesh.addObstacle({3, 3}, {8, 5});  // Implicit constructor of Point2D in arguments.

	mesh.removeObstacle(Point2D(4, 	5), Point2D(5, 4));
	mesh.addObstacle({8, 8}, {2, 2});  // Implicit constructor of Point2D in arguments.

	printMesh(mesh);
	cout << endl;
	result = tstar_mainLoop(mesh, initpoint,endpoint);
	result = astar_mainLoop(mesh, initpoint,endpoint);

	*/

	int dim = 200;
	JumpMesh mesh(dim, dim);
	int obstaclenumber = 8;
	int obstaclesize = 13;
	int c1; int c2; int c3; int c4;
	for (int i = 0; i< obstaclenumber; i++){
				c1 = 1+rand() % obstaclesize;
				c2 = 1+rand() % obstaclesize;
				c3 = 1+rand() % (dim - obstaclesize-1);
				c4 = 1+rand() % (dim - obstaclesize-1);
				mesh.addObstacle({c3,c4},{c1,c2});

	}

	printMesh(mesh);




	Point2D initpoint = {1,1};
	Point2D endpoint = {198,198};
	mesh.setTarget(endpoint);


	auto begin = std::chrono::high_resolution_clock::now();
	result = tstar_mainLoop(mesh, initpoint,endpoint);


	auto end = std::chrono::high_resolution_clock::now();
	myfile << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()<<",";

	begin = std::chrono::high_resolution_clock::now();
	result = astar_mainLoop(mesh, initpoint,endpoint);
	end = std::chrono::high_resolution_clock::now();
	myfile << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()<<",";

	myfile.close();


	return EXIT_SUCCESS;
}
