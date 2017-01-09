#ifndef SIMPLE_MESH_HPP_INCLUDED
#define SIMPLE_MESH_HPP_INCLUDED

#include "generic_mesh.hpp"

/* Simple 4-connected rectangular 2D mesh with obstacles.

Optimized like a mule on a skating rink.
*/
class SimpleMesh: public AnyAngleMesh {
public:
	SimpleMesh(const int width, const int height);
	~SimpleMesh();

	/* Add rectangular obstacle */
	void addObstacle(Point2D &org, Point2D &size);
};

#endif // SIMPLE_MESH_HPP_INCLUDED
