#ifndef SIMPLE_MESH_HPP_INCLUDED
#define SIMPLE_MESH_HPP_INCLUDED

#include <valarray>
#include "generic_mesh.hpp"

/* Simple 4-connected rectangular 2D mesh with obstacles.

Obstacles can be boolean combinations of non-rotated rect-
angles with non-negative width and height.

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
	friend void printMesh(const SimpleMesh &mesh);
private:
	void setSubRect(const Point2D &org, const Point2D &shape, int value);
};

#endif // SIMPLE_MESH_HPP_INCLUDED
