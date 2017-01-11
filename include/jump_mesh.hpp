#ifndef JUMP_MESH_HPP_INCLUDED
#define JUMP_MESH_HPP_INCLUDED

#include <set>
#include "simple_mesh.hpp"

class JumpMesh() : public SimpleMesh {
    std::map<int> vert;
    std::map<int> hor;
public:
    JumpMesh(const int width, const int height) :
        SimpleMesh(width, height) {};
    JumpMesh(const Point2D &shape) :
        SimpleMesh(shape) {};
};

#endif // JUMP_MESH_HPP_INCLUDED
