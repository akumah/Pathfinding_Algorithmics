#include "point2d.hpp"

int manhattanDist(const Point2D &diff) {
	return std::abs(diff.x) + std::abs(diff.y);
}

int manhattanDist(const Point2D &from, const Point2D &to) {
	const Point2D diff = to - from;
	return manhattanDist(diff);
}

float euclideanDist(const Point2D &diff) {
	return float(sqrt(diff.x*diff.x + diff.y*diff.y));
}

float euclideanDist(const Point2D &from, const Point2D &to) {
	const Point2D diff = to - from;
	return euclideanDist(diff);
}

std::ostream & operator<<(std::ostream &os, const Point2D &point) {
	os << "(" << point.x << ", " << point.y << ")";
	return os;
};
