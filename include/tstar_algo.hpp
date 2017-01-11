#include <iostream> 
#include <cstdlib>  
#include <cmath> 
#include "simple_mesh.hpp"
#include "point2d.hpp"
using namespace std;
class vertex_s{
	
	vertex_s* parent;	
	int gvalue = 0;
	
	public:
	int x; int y;
	vertex_s(int, int);
	vertex_s(Point2D);
	vertex_s();
	
	vector<Point2D> result;
	
	vertex_s* get_parent();
	void set_parent(vertex_s* par);
	
	int get_gvalue();
	void set_gvalue(int gval);
	
	Point2D get_point();
	void set_point(Point2D p1);
	
	bool operator==(const vertex_s &other) const {
        return (x == other.x && y == other.y);
    }

    bool operator!=(const vertex_s &other) const {
        return !(x == other.x && y == other.y);
    }

	double straight_distance(vertex_s othervertex);
};


void tstar_UpdateVertex (vertex_s* temp_s, vertex_s* near_s, SimpleMesh meshgrid, vector<vertex_s>* open);
void tstar_ComputeCost (vertex_s* s0, vertex_s* s1, SimpleMesh meshgrid );
bool tstar_lineofsight(vertex_s s0, vertex_s s1, SimpleMesh meshgrid);
vector<Point2D> tstar_mainLoop (SimpleMesh meshgrid, Point2D initpoint, Point2D endpoint);