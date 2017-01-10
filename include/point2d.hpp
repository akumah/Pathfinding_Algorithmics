#ifndef POINT2D_HPP_INCLUDED
#define POINT2D_HPP_INCLUDED

#include <iostream>
#include <cmath>  /* sqrt */

/* Maybe I should just use a valarray for it... */
struct Point2D {
	int x, y;  // Public by default, as this is a struct
public:
	Point2D() : x(0), y(0) {};
	Point2D(const int x_in, const int y_in) : x(x_in), y(y_in) {};
	Point2D(const Point2D &other) : x(other.x), y(other.y) {};
	~Point2D() {};

	Point2D & operator=(const Point2D &other) {
		x=other.x;
		y=other.y;
		return *this;
	};

	Point2D & operator+=(const Point2D &other) {
		x = x + other.x;
		y = y + other.y;
		return *this;
	}

	const Point2D & operator+(const Point2D &other) const {
		return Point2D(*this) += other;
	}

	Point2D & operator-=(const Point2D &other) {
		x = x - other.x;
		y = y - other.y;
		return *this;
	}

	const Point2D & operator-(const Point2D &other) const {
		return Point2D(*this) -= other;
	}

	bool operator==(const Point2D &other) const {
        return (x == other.x && y == other.y);
    }

    bool operator!=(const Point2D &other) const {
        return !(x == other.x && y == other.y);
    }


};

int manhattanDist(const Point2D &diff) {
	return abs(diff.x) + abs(diff.y);
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

#endif // POINT2D_HPP_INCLUDED
