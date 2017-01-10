#include <cassert>
#include <cmath>  /* For INFINITY */
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

bool SimpleMesh::getArrayValue(const int x, const int y) const {
	return d_data[y*d_shape.x + x];
}

bool SimpleMesh::getArrayValue(const Point2D &point) const {
	return getArrayValue(point.x, point.y);
}

bool SimpleMesh::isAccessible(const Point2D& point) const {
	if (isInBounds(point)) {
		return !getArrayValue(point);
	}
	else {
		return false;
	}
}

bool SimpleMesh::isInBounds(const Point2D &point) const {
	return ((point.x >= 0) && (point.x < d_shape.x) && (point.y >= 0) && (point.y < d_shape.y));
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
	if (from == to) {  // A location can always see itself.
		return true;
	}
	if (!isAccessible(to)) {  //target location must be accessible.
		return false;
	}
	if (!isInBounds(from)) { // from location is out of bounds
		return false;
	}
	const Point2D diff = to - from;
	if (diff.x != 0) {  // if the line is not vertical
		/* find a function in terms of x for the line */
		const float ay = diff.y / (diff.x * 1.0); /*< Slope in x */
		const float by = from.y - ay * from.x;  /*< Intercept in x */
		auto yfunc = [&](int x){return ay * x + by;};
		const int dirx = sgn(diff.x);  /*< Direction to iterate x in */
		for (int x=from.x+1; x!=to.x; x += dirx){
			int y = int(floor(yfunc(x)));  // The floor is important for negative values //
			if (getArrayValue(x, y) && getArrayValue(x, y+1)) {
				return false;  // Encountered a vertical wall.
			}
		}
	}

	/* If program flow has reached here, then that means that no obstacle
	 * was found by scanning through x, or that diff.x == 0 */
	if (diff.y != 0) {
		/* Find the line function in terms of y */
		const float ax = diff.x / (diff.y * 1.0); /*< Slope in y */
		const float bx = from.x - ax * from.y;  /*< Intercept in y */
		auto xfunc = [&](int y){return ax * y + bx;};
		const int diry = sgn(diff.y);  /*< Direction to iterate x in */
		for (int y=from.y+1; y!=to.y; y += diry){
			int x = int(floor(xfunc(y)));  // The floor is important for negative values //
			if (getArrayValue(x, y) && getArrayValue(x+1, y)) {
				return false;  // Encountered a horizontal wall.
			}
		}
	}
	return true;  // Neither vertical nor horizontal walls were found.


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
			char out = mesh.getArrayValue(x, y) ? obstacle : free;
			std::cout << out;
		}
		std::cout << std::endl;
	}
}



