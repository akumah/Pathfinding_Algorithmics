
#include <iostream>
#include <unordered_set>
#include "simple_mesh.hpp"

using namespace std;
void print_header() {
	cout << "\n\t\tSIMPLE_MESH TEST\n" << endl;
	cout << "All tests should print 1 if successful." << endl;
	cout << "When mesh graphic is output, it needs visual confirmation.\n\n" << endl;
}

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

/* Test creation of SimpleMesh.

Tests creation, obstacle addition and removal, getArrayValue and output.
*/
bool test_SimpleMesh_creation() {
	SimpleMesh mesh(15, 10);
	mesh.addObstacle(Point2D(3, 3), Point2D(8,5));
	mesh.removeObstacle(Point2D(4, 4), Point2D(5, 3));
	printMesh(mesh);
	cout << endl;
	return true; //Assume that reaching here is success. Validate output visually.
}

bool test_SimpleMesh_getShape() {
	SimpleMesh mesh(15, 10);
	return (mesh.getShape() == Point2D(15, 10));
}

void test_SimpleMesh_isAccessible() {
	SimpleMesh mesh(15, 10);

	cout << "\t\tTesting bounds checking:" << endl;
	/* Check that out-of-bounds checking works */
	Point2D point(0, 0);
	cout << "\t\t" << point << " : " << mesh.isAccessible(point) << endl;
	point = Point2D(14, 9);
	cout << "\t\t" << point << " : " << mesh.isAccessible(point) << endl;
	point = Point2D(-1, 0);
	cout << "\t\t" << point << " : " << !mesh.isAccessible(point) << endl;
	point = Point2D(15, 0);
	cout << "\t\t" << point << " : " << !mesh.isAccessible(point) << endl;
	point = Point2D(0, -1);
	cout << "\t\t" << point << " : " << !mesh.isAccessible(point) << endl;
	point = Point2D(0, 10);
	cout << "\t\t" << point << " : " << !mesh.isAccessible(point) << endl;
	point = Point2D(15, 10);
	cout << "\t\t" << point << " : " << !mesh.isAccessible(point) << endl;
	/* Check that obstacle checking works */
	cout << "\t\tTesting obstacle checking:" << endl;
	mesh.addObstacle(Point2D(0,0), Point2D(1,1));
	point = Point2D(0, 0);
	cout << "\t\t" << point << " : " << !mesh.isAccessible(point) << endl;
}

void test_SimpleMesh_getDistance() {
	SimpleMesh mesh(15, 10);
	Point2D from(0, 0);
	Point2D to(0, 0);
	cout << "\t\t" << from << to << " : " << (mesh.getDistance(from, to) == 0) << endl;
	to = Point2D(-1, 0);
	cout << "\t\t" << from << to << " : " << (mesh.getDistance(from, to) == 1) << endl;
	to = Point2D(1, 0);
	cout << "\t\t" << from << to << " : " << (mesh.getDistance(from, to) == 1) << endl;
	to = Point2D(0, -1);
	cout << "\t\t" << from << to << " : " << (mesh.getDistance(from, to) == 1) << endl;
	to = Point2D(0, 1);
	cout << "\t\t" << from << to << " : " << (mesh.getDistance(from, to) == 1) << endl;
	to = Point2D(1, 1);
	cout << "\t\t" << from << to << " : " << (mesh.getDistance(from, to) - 1.414213562 < 0.00001) << endl;
	to = Point2D(-1, -1);
	cout << "\t\t" << from << to << " : " << (mesh.getDistance(from, to) - 1.414213562 < 0.00001) << endl;
	to = Point2D(-2, -4);  //Point2D euclideanDist
	cout << "\t\t" << from << to << " : " << (mesh.getDistance(from, to) - 4.472135954 < 0.00001) << endl;
}

bool test_SimpleMesh_getHeuristic() {
	SimpleMesh mesh(15, 10);
	Point2D from(0, 0);
	Point2D to(-2, -4);
	return (mesh.getDistance(from, to) - 4.472135954 < 0.00001);
}

bool test_SimpleMesh_getNeighbours() {
	SimpleMesh mesh(15, 10);
	mesh.addObstacle(Point2D(0, 1), Point2D(1,1));
	std::vector<Point2D> expected1({Point2D(1, 0)});
	std::vector<Point2D> neighbours1(mesh.getNeighbours(Point2D(0, 0)));
	std::vector<Point2D> expected2({Point2D(6, 4), Point2D(6, 6), Point2D(5, 5), Point2D(7, 5)});
	std::vector<Point2D> neighbours2(mesh.getNeighbours(Point2D(6, 5)));
	return (expected1 == neighbours1 && expected2 == neighbours2);
}

void test_SimpleMesh_isVisible() {
	SimpleMesh mesh(15, 10);
	mesh.addObstacle(Point2D(3,3), Point2D(1,3));
	mesh.addObstacle(Point2D(0,7), Point2D(3,1));
	printMesh(mesh);
	Point2D from(2, 5);
	Point2D to(2, 5);
	cout << "\t\tSelf-visibility" << endl;
	cout << "\t\t" << from << to << " : " << (mesh.isVisible(from, to)) << endl;
	from = Point2D(3, 5);
	to = Point2D(3, 5);
	cout << "\t\t" << from << to << " : " << (mesh.isVisible(from, to)) << endl;
	cout << "\t\tNon-accessible" << endl;
	from = Point2D(2, 5);
	to = Point2D(-2, 5);
	cout << "\t\t" << from << to << " : " << !(mesh.isVisible(from, to)) << endl;
	to = Point2D(3, 5);
	cout << "\t\t" << from << to << " : " << !(mesh.isVisible(from, to)) << endl;
	cout << "\t\tObstacle visibility" << endl;
	to = Point2D(4, 4);
	cout << "\t\t" << from << to << " : " << !(mesh.isVisible(from, to)) << endl;
	to = Point2D(4, 6);
	cout << "\t\t" << from << to << " : " << (mesh.isVisible(from, to)) << endl;
	to = Point2D(1, 8);
	cout << "\t\t" << from << to << " : " << !(mesh.isVisible(from, to)) << endl;
	to = Point2D(3, 8);
	cout << "\t\t" << from << to << " : " << (mesh.isVisible(from, to)) << endl;
	cout << "\t\tObstacle visibility" << endl;
	from = Point2D(4, 4);
	to = Point2D(2, 5);
	cout << "\t\t" << from << to << " : " << !(mesh.isVisible(from, to)) << endl;
	from = Point2D(4, 6);
	cout << "\t\t" << from << to << " : " << (mesh.isVisible(from, to)) << endl;
	from = Point2D(1, 8);
	cout << "\t\t" << from << to << " : " << !(mesh.isVisible(from, to)) << endl;
	from = Point2D(3, 8);
	cout << "\t\t" << from << to << " : " << (mesh.isVisible(from, to)) << endl;


}

int main(){
	print_header();
    cout << "Testing Point2D:" << endl;
	cout << "\tPoint2D output: " << test_Point2D_out() << endl;
	cout << "\tPoint2D equality: " << test_Point2D_equality() << endl;
    cout << "\tPoint2D assignment: " << test_Point2D_assignment() << endl;
	cout << "\tPoint2D subtract and copy-construct: " << test_Point2D_subtract() << endl;
	cout << "\tPoint2D add: " << test_Point2D_add() << endl;
	cout << "\tPoint2D manhattanDist: " << test_Point2D_manhattan() << endl;
	cout << "\tPoint2D euclideanDist: " << test_Point2D_euclidean() << endl;
	cout << "Done Point2D.\n" << endl;

	cout << "Testing SimpleMesh:" << endl;
	cout << "\tSimpleMesh creation: " << test_SimpleMesh_creation() << endl;
	cout << "\tSimpleMesh getShape: " << test_SimpleMesh_getShape() << endl;
	cout << "\tSimpleMesh isAccessible:" << endl;
	test_SimpleMesh_isAccessible();
	cout << "\tSimpleMesh getDistance:" << endl;
	test_SimpleMesh_getDistance();
	cout << "\tSimpleMesh getHeuristic: " << test_SimpleMesh_getHeuristic() << endl;
	cout << "\tSimpleMesh getNeighbours: " << test_SimpleMesh_getNeighbours() << endl;
	cout << "\tSimpleMesh isVisible:" << endl;
	test_SimpleMesh_isVisible();

}
