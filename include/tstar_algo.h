#include <iostream> 
#include <cstdlib>  
#include <cmath> 
using namespace std;
class vertex_s{
	
	vertex_s* parent;
	int gvalue;
	
	public:
	int x; int y;
	vertex_s(int, int);
	
	vertex_s getParent();
	void setParent(vertex_s* par);
	
	int get_gvalue();
	void set_gvalue(int gval);
	
	double straight_distance(vertex_s othervertex);
};

vertex_s vertex_s::getParent(){
	return *parent;
}

void vertex_s::setParent(vertex_s* par){
	parent = par;
}
vertex_s::vertex_s(int x_init, int y_init){
	x = x_init;
	y = y_init;
}
int vertex_s::get_gvalue(){
	return gvalue;
}
void vertex_s::set_gvalue(int gval){
	gvalue = gval;
}

double vertex_s::straight_distance(vertex_s othervertex){
	int d1; int d2;
	double distance;
	if (othervertex.x >= x) d1 = othervertex.x - x;
	else d1 = x - othervertex.x;
	
	if (othervertex.y >= y) d2 = othervertex.y - y;
	else d2 = y - othervertex.y;
	
	distance= sqrt(d1*d1 + d2*d2);
	return distance;
}
//[column1[row1,row2... rowN], column2[row1,row2... rowN]...columnN[row1,row2... rowN]], where column is y and row is x is the current format of the grid
class grid{
	public:
	bool[][] gridcoordinates;
	grid(bool[][]);
	
	bool isBlocked(int x, int y);
};

grid::grid(bool[][] coords){
	gridcoordinates = coords;
}

grid::isBlocked(int x, int y)


void tstar_UpdateVertex (int *arrays, int arraylength);
void tstar_ComputeCost (int *arrays, int arraylength);
