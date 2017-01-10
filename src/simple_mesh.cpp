#include <cassert>
#include "simple_mesh.hpp"

void SimpleMesh::addObstacle(const Point2D &org, const Point2D &shape) {
	setSubRect(org, shape, true);
}

void SimpleMesh::removeObstacle(const Point2D &org, const Point2D &shape) {
	setSubRect(org, shape, false);
}

/* Set the value of all elements in a subrectangle of mesh to value */
void SimpleMesh::setSubRect(const Point2D& org, const Point2D& shape, int value) {
	int start_idx = org.y * d_shape.x + org.x;
	d_data[std::gslice(start_idx, {shape.y, shape.x}, {d_shape.x, 1})] = value;
}

bool SimpleMesh::isAccessible(const Point2D& point) const {
	if ((point.x >= 0) && (point.x < d_shape.x) && (point.y >= 0) && (point.y < d_shape.y)){
		return !d_data[point.y*d_shape.x + point.x];
	}
	else {
		return false;
	}
}

float SimpleMesh::getDistance(const Point2D& from, const Point2D& to) const {
	const float n_d = 1.414213562;  // Distance of a diagonal neighbour
	if (from == to) {
		return 0.0;
	}
	Point2D diff = to - from;
	if (abs(diff.x) + abs(diff.y) == 1) {  // Manhattan distance
		return 1.0;
	}
	if (abs(diff.x) == 1 && abs(diff.y) == 1) {
		return n_d;
	}
	return euclideanDist(from, to);
}

float SimpleMesh::getHeuristic(const Point2D& from, const Point2D& to) const {
	return SimpleMesh::getDistance(from, to);
}

bool SimpleMesh::isVisible(const Point2D& from, const Point2D& to) const {
//	if (from == to) {
//		return true;
//	}
//	Point2D diff = to - from;
//	int yfunc = [](int x){}
	return true;
}

std::vector<Point2D> SimpleMesh::getNeighbours(const Point2D &point) const {
	std::vector<Point2D> vec;
	vec.reserve(4);
	Point2D top = point + Point2D(0, -1);
	if (isAccessible(top)) {
		vec.push_back(top);
	}
	Point2D bot = point + Point2D(0, 1);
	if (isAccessible(bot)) {
		vec.push_back(bot);
	}
	Point2D lef = point + Point2D(-1, 0);
	if (isAccessible(lef)) {
		vec.push_back(lef);
	}
	Point2D rig = point + Point2D(1, 0);
	if (isAccessible(rig)) {
		vec.push_back(rig);
	}
	return vec;
}

const Point2D & SimpleMesh::getShape() {
	return d_shape;
}

void printMesh(const SimpleMesh &mesh) {
	const char free = 43; //ascii char +
	const char obstacle = 219; // ascii char █
	for (int y=0; y<mesh.d_shape.y; y++) {
		for (int x=0; x<mesh.d_shape.x; x++) {
			char out = mesh.d_data[y*mesh.d_shape.x + x] ? obstacle : free;
			std::cout << out;
		}
		std::cout << std::endl;
	}
}



