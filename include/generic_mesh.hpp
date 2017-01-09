#ifndef GENERIC_MESH_HPP_INCLUDED
#define GENERIC_MESH_HPP_INCLUDED

#include <vector>
#include <ostream>

class Point2D {
public:
	Point2D();
	Point2D(const int x, const int y);
	~Point2D();

	Point2D & operator=(const Point2D &other);

};

public std::ostream & operator<<(std::ostream &os, const &Point2D);

/* Interface for a generic 2D navmesh. */
class GenericMesh {
public:
	/* Get the neighbouring points of a point. Implies visibility. */
	virtual std::vector<Point2D>  getNeighbors(Point2D &point) = 0;
	/* Get the distance from a point to another. */
	virtual float getDistance(Point2D &from, Point2D &to) = 0;
	/* Get the heuristic distance from a point to another. */
	virtual float getHeuristic(Point2D &from, Point2D &to) = 0;
	};
	/* Check whether a location is in the mesh and is not in an obstacle */
	virtual bool isAccessible(Point2D &point)

/* Interface for a generic 2D navmesh that can be used in any-angle algorithms.

Adds isVisible method used for shortcut viability in any-angle path planners.
Implies obstacles or concave borders.
*/
class AnyAngleMesh: public GenericMesh {
public:
	virtual bool isVisible(Point2D &from, Point2D &to) = 0;
};

#endif // GENERIC_MESH_HPP_INCLUDED
