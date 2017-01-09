#include "simple_mesh.hpp"

SimpleMesh::SimpleMesh(const Point2D& shape) {
	init(shape)
}

SimpleMesh::SimpleMesh(const int width, const int height) {
	shape = Point2D(width, height);
	init(shape)
}

SimpleMesh::~SimpleMesh(){}

void SimpleMesh::init(const Point2d &shape) {
	d_data(shape.x * shape.y);
	d_shape(shape);
}

void SimpleMesh::addObstacle(const Point2D &org, const Point2D &shape) {
	setSubRect(org, shape, 1);
}

void SimpleMesh::removeObstacle(const Point2D &org, const Point2D &shape) {
	setSubRect(org, shape, 0);
}

void SimpleMesh::setSubRect(const Point2D& org, const Point2D& shape, int value) {
	int start_idx = org.y * d_shape.x + org.x;
	d_data[std::gslice(start_idx, {shape.y, shape.x}, {d_shape.x, 1})] = value;
}

bool SimpleMesh::isAccessible(const Point2D& point) {
	if ((point.x >= 0) && (point.x < d_shape.x) && (point.y >= 0) && (point.y < d_shape.y)){
		return d_data[point.y*d_shape.x + point.x];
	}
	else {
		return false;
	}
}

float SimpleMesh::getDistance(const Point2D& from, const Point2D& to) {
	const float n_hv = 1;  // Distance of a horizontal or vertical neighbour
	const float n_d = 1.414213562;  // Distance of a diagonal neighbour
	Point2D diff = to - from;
	if (abs(diff.x) + abs(diff.y) == 1) {  // Manhattan distance
		return n_hv;
	}
	if (abs(diff.x) == 1 && abs(diff.y) == 1) {
		return n_d;
	}
	return euclideanDist(from, to)
}

float SimpleMesh::getHeuristic(const Point2D& from, const Point2D& to) {
	return SimpleMesh::getDistance(from, to)
}

/* Not yet implemented. Want to test if rest of the stuff works. */
bool SimpleMesh::isVisible(const Point2D& from, const Point2D& to) {
	return true;
}

std::vector<Point2D> & SimpleMesh::getNeighbours(const Point2D &point) {
	std::vector<Point2D> vec();
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

void SimpleMesh::getShape() {
	return d_shape;
}

void printMesh(const SimpleMesh &mesh) {
	const char free = 177 //ascii char ▒
	const char obstacle = 219 // ascii char █
	for (int y=0; y<mesh.d_shape.y; y++) {
		for (int x=0; x<mesh.d_shape.x; x++) {
			char out = mesh.d_data[y*mesh.d_shape.x + x] ? free : obstacle;
			std::cout << out;
		std::cout << std::endl;
		}
	}
}



