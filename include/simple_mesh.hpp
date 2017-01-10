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
	Point2D d_shape;
public:
	SimpleMesh(const int width, const int height);
	SimpleMesh(const Point2D &shape);
	~SimpleMesh();

	/* Add rectangular obstacle */
	void addObstacle(Point2D &org, Point2D &shape);

	/* Create hole in obstacle */
	void removeObstacle(Point2D &org, Point2D &shape);

	/* Get dimensions of the field */
	Point2D & getShape();
	friend void printMesh(SimpleMesh &mesh);
private:
	void init(Point2D &shape);
	void setSubRect(Point2D &org, Point2D &shape, int value);
};

/* Stream the mesh as char map to cout. Interface?*/
void printMesh(SimpleMesh &mesh);

#endif // SIMPLE_MESH_HPP_INCLUDED
