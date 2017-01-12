#include "jump_mesh.hpp"

std::vector<Point2D>
JumpMesh::getNeighbours(const Point2D &point) const {
	const_iterator vert_iter = d_vert.lower_bound(point.x);
	const_iterator hor_iter = d_hor.lower_bound(point.y);

	/* get the neighboring boundaries */
	const int left, right, up, down;
	left = point.x > 0 ? *(vert_iter - 1) : 0;
	top = point.y > 0 ? *(hor_iter - 1) : 0;
	if (*vert_iter < d_shape.x - 1) {  // If not on the field edge
		//Take the next value if we're on a value, otherwise lower_bound already gave next.
		right = (point.x == *(vert_iter)) ? *(vert_iter + 1) : point.x;
	}
	else { // If we're on the edge, then we're on the edge.
		right = d_shape.x - 1;
	}
	if *hor_iter < d_shape.y - 1) {
		bottom = (point.y == *hor_iter) ? *(hor_iter + 1) : point.y;
	}
	else {
		bottom = d_shape.y - 1;
	}
	// If target is in the rectangle, switch to classical mesh
	if d_target.x <= right
}
