#ifndef POINT2D_HPP_INCLUDED
#define POINT2D_HPP_INCLUDED

#include <cmath>  /* sqrt */
#include <iostream>
#include <array>

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

/* From http://stackoverflow.com/a/8026914 */
namespace std
{
    template<typename T, size_t N>
    struct hash<array<T, N> >
    {
        typedef array<T, N> argument_type;
        typedef size_t result_type;

        result_type operator()(const argument_type& a) const
        {
            hash<T> hasher;
            result_type h = 0;
            for (result_type i = 0; i < N; ++i)
            {
                h = h * 31 + hasher(a[i]);
            }
            return h;
        }
    };
}

namespace std {
  template <> struct hash<Point2D>
  {
    size_t operator()(const Point2D & point) const
    {
      return hash<array<int, 2>>()({point.x, point.y});
    }
  };
}

int manhattanDist(const Point2D &diff);

int manhattanDist(const Point2D &from, const Point2D &to);

float euclideanDist(const Point2D &diff);

float euclideanDist(const Point2D &from, const Point2D &to);

std::ostream & operator<<(std::ostream &os, const Point2D &point);

#endif // POINT2D_HPP_INCLUDED
