#ifndef JUMP_MESH_HPP_INCLUDED
#define JUMP_MESH_HPP_INCLUDED

#include <iostream>
#include <set>
#include "utility.hpp"
#include "simple_mesh.hpp"

class JumpMesh : public SimpleMesh {
	/* Storage for the obstacle edges */
    std::set<int> d_vert;
    std::set<int> d_hor;
public:
    JumpMesh(const int width, const int height)
    :   SimpleMesh(width, height),
        d_vert({0, width - 1}),
        d_hor({0, height - 1}) {
	};
    JumpMesh(const Point2D &shape) :
        SimpleMesh(shape),
        d_vert({0, shape.x - 1}),
        d_hor({0, shape.y - 1}) {
	};
	~JumpMesh() {};

	void addObstacle(const Point2D &org, const Point2D &shape) {
		SimpleMesh::addObstacle(org, shape);
		d_vert.insert({org.x - 1, org.x + shape.x + 1});
		d_hor.insert({org.y - 1, org.y + shape.y +1});
	};
	void removeObstacle(const Point2D &, const Point2D &) {
		std::cerr << "WARNING: JumpMesh does not support obstacle removal!" << std::endl;
	}

	std::vector<Point2D> getNeighbours(const Point2D &point) const;
	void setTarget(const Point2D &point) {d_target = point;};
};

#endif // JUMP_MESH_HPP_INCLUDED
