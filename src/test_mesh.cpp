
#include <iostream>
#include "simple_mesh.hpp"

using namespace std;
bool test_Point2D_out() {
    Point2D point(3,2);
	cout << point << endl;
	return true;  //Assume that if it reaches here, then everything's okay
}

bool test_Point2D_equality() {
    Point2D point1(3,2);
    Point2D point2(3,2);
    Point2D point3(3,3);
	return (point1 == point2 && point1 != point3);
}

bool test_Point2D_assignment() {
    Point2D point1(3,3);
    Point2D point2(2,2);
    Point2D point3(3,3);
    point2 = point3;
	return (point1 == point2);
}

/* Test a - b. As it's defined in terms of c(a), c-=b, it also tests -= and copy-construct*/
bool test_Point2D_subtract() {
    Point2D point1(3,2);
    Point2D point2(2,1);
    Point2D point3(-1,-1);
	return (point2 - point1 == point3);
}

bool test_Point2D_add() {
    Point2D point1(3,2);
    Point2D point2(2,1);
    Point2D point3(5,3);
	return (point1 + point2 == point3);
}

bool test_Point2D_manhattan() {
    Point2D point1(-3,2);
    Point2D point2(2,1);
    int expected = 6;
	return (manhattanDist(point1, point2) == expected);
}
bool test_Point2D_euclidean() {
    Point2D point1(-3,2);
    Point2D point2(2,1);
    float expected = 5.0990195135;
    float result = euclideanDist(point1, point2);
	return (result == expected);
}

int main(){
    cout << "Testing Point2D:" << endl;
	cout << "\tPoint2D output: " << test_Point2D_out() << endl;
	cout << "\tPoint2D equality: " << test_Point2D_equality() << endl;
    cout << "\tPoint2D assignment: " << test_Point2D_assignment() << endl;
	cout << "\tPoint2D subtract and copy-construct: " << test_Point2D_subtract() << endl;
	cout << "\tPoint2D add: " << test_Point2D_add() << endl;
	cout << "\tPoint2D manhattanDist: " << test_Point2D_manhattan() << endl;
	cout << "\tPoint2D euclideanDist: " << test_Point2D_euclidean() << endl;
}
