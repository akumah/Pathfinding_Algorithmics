#ifndef SIMPLE_MESH_HPP_INCLUDED
#define SIMPLE_MESH_HPP_INCLUDED

#include <valarray>
#include "generic_mesh.hpp"

/* Since the STL doesn't include one: sgn function
Courtesy of user79758, http://stackoverflow.com/a/4609795/3745323
*/
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

/* Simple 4-connected rectangular 2D mesh with obstacles.

Obstacles can be boolean combinations of non-rotated rect-
angles with non-negative width and height. The locations define
the edges of the obstacle.

For getNeighbours, isVisible etc. there is asymmetry in that
starting from the edge of an obstacle is possible, but finishing there
is not.

Optimized like a mule on a skating rink.
*/
class SimpleMesh: public AnyAngleMesh {
	std::valarray<bool> d_data;
	const Point2D d_shape;  // This should not change, once initialized.
public:
	SimpleMesh(const int width, const int height) :
		d_data(width*height), d_shape(width, height) {};
	SimpleMesh(const Point2D &shape) :
		d_data(shape.x*shape.y), d_shape(shape) {};
	~SimpleMesh() {};

	/* Pure virtuals from the interface */
	std::vector<Point2D> getNeighbours(const Point2D &point) const;
	bool isAccessible(const Point2D& point) const;
	float getDistance(const Point2D& from, const Point2D& to) const;
	float getHeuristic(const Point2D& from, const Point2D& to) const;
	bool isVisible(const Point2D& from, const Point2D& to) const;


	/* Add rectangular obstacle */
	void addObstacle(const Point2D &org, const Point2D &shape);

	/* Create hole in obstacle */
	void removeObstacle(const Point2D &org, const Point2D &shape);

	/* Get dimensions of the field */
	const Point2D & getShape();
	bool isInBounds(const Point2D &point) const;
	friend void printMesh(const SimpleMesh &mesh);
private:
	void setSubRect(const Point2D &org, const Point2D &shape, int value);
	bool getArrayValue(const int x, const int y) const;
	bool getArrayValue(const Point2D &point) const;
};

#endif // SIMPLE_MESH_HPP_INCLUDED
