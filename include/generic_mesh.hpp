#ifndef GENERIC_MESH_HPP_INCLUDED
#define GENERIC_MESH_HPP_INCLUDED

#include <vector>
#include "point2d.hpp

/* Interface for a generic 2D navmesh. */
class GenericMesh {
public:
	/* Get the neighbouring points of a point. Implies visibility. */
	virtual std::vector<Point2D> & getNeighbours(const Point2D &point) = 0;
	/* Get the distance from a point to another. */
	virtual float getDistance(const Point2D &from, const Point2D &to) = 0;
	/* Get the heuristic distance from a point to another. */
	virtual float getHeuristic(const Point2D &from, const Point2D &to) = 0;
	/* Check whether a location is in the mesh and is not in an obstacle */
	virtual bool isAccessible(const Point2D &point) = 0;
	};

/* Interface for a generic 2D navmesh that can be used in any-angle algorithms.

Adds isVisible method used for shortcut viability in any-angle path planners.
Implies obstacles or concave borders.
*/
class AnyAngleMesh: virtual public GenericMesh {
public:
	virtual bool isVisible(const Point2D &from, const Point2D &to) = 0;
};

#endif // GENERIC_MESH_HPP_INCLUDED
