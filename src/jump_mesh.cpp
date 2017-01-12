#include "jump_mesh.hpp"

std::vector<Point2D>
JumpMesh::getNeighbours(const Point2D &point) const {
	std::set<int>::const_iterator vert = d_vert.lower_bound(point.x);
	std::set<int>::const_iterator hor = d_hor.lower_bound(point.y);
	std::vector<Point2D> vec;

	/* Check whether the point is on any lines. If it is, then lower_bound
	 * should have returned a pointer to a value equal to it.
	 */
	int left, right, up, down;
	const bool x_on_line = (point.x == *vert);
	const bool y_on_line = (point.y == *hor);

	/* This is the usual operating case, after routing has reached the major grid.
	 * Rest of the cases are needed to get from an arbitrary point to the grid.*/
	if (x_on_line && y_on_line) {
		/* In any case x > 0 there is a line before it: the 0 line
		 * that was added by the contructor. Same for the other sides.
		 */
		left = (point.x > 0) ? *(std::prev(vert)) : 0;
		right = (point.x < d_shape.x - 1) ? *(std::next(vert)) : (d_shape.x - 1);
		up = (point.y > 0) ? *(std::prev(hor)) : 0;
		down = (point.y < d_shape.y - 1) ? *(std::next(hor)) : (d_shape.y - 1);

		/* Check if perhaps the target is already in sight. */
		if (((d_target.x < right && d_target.x > left) || d_target.x == point.x) &&
			((d_target.y < down && d_target.y > up) || d_target.y == point.y)) {
				vec.push_back({d_target});
			}
		else { /* Return the neighbouring grid intersections */
		if (point.x > 0) vec.push_back({left, point.y});
		if (point.x < d_shape.x - 1) vec.push_back({right, point.y});
		if (point.y > 0) vec.push_back({point.x, up});
		if (point.y < d_shape.y - 1) vec.push_back({point.x, down});
		}
	}
	else if (x_on_line) {  // Implicitly y_on_line is false.
		/* No need to check whether point.y is on the boundary, as
		 * if it were, it would also be on a line. Only two or one
		 * points are returned, as anything else risks colliding with
		 * obstacle, unless additional checks are made.
		 */
		vec.push_back({point.x, *(std::prev(hor))});
		vec.push_back({point.x, *(hor)}); // hor already points to the next higher line.
	}
	else if (y_on_line) {
		vec.push_back({*(std::prev(vert)), point.y});
		vec.push_back({*(vert), point.y});
	}
	else {
		/* If the grid cell is empty then just return all corners of it.
		 * Otherwise use the point-by-point neighbour algorithm from SimpleMesh.
		 * Whether the cell is empty can be determined by whether the obstacle flag for the
		 * point itself is raised. If one point inside a cell is obstacle, then all are,
		 * and pathing is only possible from the edge of an obstacle.
		 */
		if (getArrayValue(point))  {
			vec = SimpleMesh::getNeighbours(point);
		}
		else {
			vec.push_back({*(std::prev(vert)), *(std::prev(hor))});
			vec.push_back({*(vert), *(std::prev(hor))});
			vec.push_back({*(vert), *(hor)});
			vec.push_back({*(std::prev(vert)), *(hor)});
		}

	}
	return vec;
}
