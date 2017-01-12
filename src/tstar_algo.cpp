#include <iostream> /* Sisend ja väljund */
#include <cstdlib>  /* EXIT_SUCCESS jt konstandid */
#include "tstar_algo.hpp"
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <list>
using namespace std; /* Nimeruumi valik (selgitatakse praktikumis) */


vertex_s* vertex_s::get_parent(){
	return parent;
}

void vertex_s::set_parent(vertex_s* par){
	parent = par;
}
vertex_s::vertex_s(int x_init, int y_init){
	x = x_init;
	y = y_init;
}
vertex_s::vertex_s(Point2D p1){
	x = p1.x;
	y = p1.y;
}
vertex_s::vertex_s(){
}

Point2D vertex_s::get_point(){
	return {x,y};
}

void vertex_s::set_point(Point2D p1){
	x = p1.x;
	y = p1.y;
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
/*
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
*/
void tstar_UpdateVertex (unordered_map<Point2D,vertex_s>* parentmap,vertex_s s_goal, vertex_s* temp_s, vertex_s* near_s, SimpleMesh meshgrid, map<float,vertex_s>* openmap){
	int g_old = near_s->get_gvalue();
	//printf("%d %d \n", temp_s->get_point().x,temp_s->get_point().y);
	//printf("%d %d \n", near_s->get_point().x,near_s->get_point().y);

	tstar_ComputeCost(parentmap,temp_s, near_s, meshgrid);
	//printf("gvalue test: %d \n ", near_s->get_gvalue());
	//printf("gold test: %d \n ", g_old);

	if (near_s->get_gvalue() < g_old){

		std::map<float,vertex_s>::iterator it = openmap->begin();
		//it = std::find(openmap.begin(), openmap.end(),*near_s);
		for (it = openmap->begin(); it != openmap->end(); ++it ){
			if (it->second == *near_s){
				openmap->erase(it);
			}
			//printf("smalleropen \n");
		}
		//printf("biggeropen \n");
		openmap->insert(pair<float,vertex_s>(near_s->get_gvalue()+meshgrid.getDistance(near_s->get_point(), s_goal.get_point()), *near_s ));
	}
}

void astar_UpdateVertex (unordered_map<Point2D,vertex_s>* parentmap,vertex_s s_goal, vertex_s* temp_s, vertex_s* near_s, SimpleMesh meshgrid, map<float,vertex_s>* openmap){
	int g_old = near_s->get_gvalue();
	//printf("%d %d \n", temp_s->get_point().x,temp_s->get_point().y);
	//printf("%d %d \n", near_s->get_point().x,near_s->get_point().y);

	astar_ComputeCost(parentmap,temp_s, near_s, meshgrid);
	//printf("gvalue test: %d \n ", near_s->get_gvalue());
	//printf("gold test: %d \n ", g_old);

	if (near_s->get_gvalue() < g_old){

		std::map<float,vertex_s>::iterator it = openmap->begin();
		//it = std::find(openmap.begin(), openmap.end(),*near_s);
		for (it = openmap->begin(); it != openmap->end(); ++it ){
			if (it->second == *near_s){
				openmap->erase(it);
			}
			//printf("smalleropen \n");
		}
		//printf("biggeropen \n");
		openmap->insert(pair<float,vertex_s>(near_s->get_gvalue()+meshgrid.getDistance(near_s->get_point(), s_goal.get_point()), *near_s ));
	}
}


void tstar_ComputeCost(unordered_map<Point2D,vertex_s>* parentmap, vertex_s* s0, vertex_s* s1, SimpleMesh meshgrid ){
	std::unordered_map<Point2D,vertex_s>::iterator it;
	it = parentmap->find(s0->get_parent()->get_point());
	vertex_s* aword;
	if (it != parentmap->end()){
				//parentmap->emplace(pair<Point2D,vertex_s>(s0->get_parent()->get_point(), *s1));
		vertex_s awordnon = it->second;
		aword = &awordnon;}
	else{
		parentmap->emplace(pair<Point2D,vertex_s>(s0->get_point(), *s0));
		s0->set_parent(s0);
		aword = s0;
	}
	//printf("here is fine right \n");
	//printf("X value is test Computecost: %d \n ",s0->x);
	//printf("computecost test");
	//printf("%d %d \n", aword->get_point().x,aword->get_point().y);
	//printf("%d %d \n", s1->get_point().x,s1->get_point().y);

	
	//if (tstar_lineofsight(*aword, *s1, meshgrid)){
	if (meshgrid.isVisible(aword->get_point(), s1->get_point())){
		if (aword->get_gvalue()+meshgrid.getDistance(aword->get_point(), s1->get_point()) < s1->get_gvalue()){
			
			
			std::unordered_map<Point2D,vertex_s>::iterator it;
			s1->set_parent(aword);
			it = parentmap->find(s0->get_parent()->get_point());
			if (it != parentmap->end()){
				//parentmap->emplace(pair<Point2D,vertex_s>(s0->get_parent()->get_point(), *s1));
				parentmap->emplace(pair<Point2D,vertex_s>(s1->get_point(), *aword));
			}
			else{
				printf("am here");
				it->second = vertex_s(s1->get_point());
			}
			//std::cerr << "if" << s1->get_point() << std::endl;
			/*if (!parenttest){ 
				parentmap->erase(it);
				parentmap->emplace(pair<Point2D,vertex_s>(s0->get_parent()->get_point(), *s1));
			}*/
			s1->set_gvalue(aword->get_gvalue()+meshgrid.getDistance(aword->get_parent()->get_point(), s1->get_point()));
		}
	}
	else{
		if ((s0->get_gvalue() + meshgrid.getDistance(s0->get_point(), s1->get_point()))< s1->get_gvalue()){
			//printf("parent change2\n");
			std::unordered_map<Point2D,vertex_s>::iterator it;
			s1->set_parent(s0);
			it = parentmap->find(s0->get_parent()->get_point());
			if (it != parentmap->end()){
				parentmap->emplace(pair<Point2D,vertex_s>(s1->get_point(), *s0));
			}
			else{
				it->second = *s0;
			}
			/*
			if (!parenttest){ 
				parentmap->erase(it);
				parentmap->emplace(pair<Point2D,vertex_s>(s0->get_parent()->get_point(), *s1));
			}*/
			//std::cerr << "else" << s1->get_point() << std::endl;
			s1->set_gvalue(s0->get_gvalue() + meshgrid.getDistance(s0->get_point(), s1->get_point()));
		}
	}
}

void astar_ComputeCost (unordered_map<Point2D,vertex_s>* parentmap, vertex_s* s0, vertex_s* s1, SimpleMesh meshgrid ){
std::unordered_map<Point2D,vertex_s>::iterator it;
	it = parentmap->find(s0->get_parent()->get_point());
	vertex_s* aword;
	if (it != parentmap->end()){
				//parentmap->emplace(pair<Point2D,vertex_s>(s0->get_parent()->get_point(), *s1));
		vertex_s awordnon = it->second;
		aword = &awordnon;}
	else{
		aword = s0->get_parent();
	}
	//if (tstar_lineofsight(*aword, *s1, meshgrid)){
	if ((s0->get_gvalue() + meshgrid.getDistance(s0->get_point(), s1->get_point()))< s1->get_gvalue()){
		//printf("parent change2\n");
		std::unordered_map<Point2D,vertex_s>::iterator it;
		s1->set_parent(s0);
		it = parentmap->find(s0->get_parent()->get_point());
		if (it != parentmap->end()){
			parentmap->emplace(pair<Point2D,vertex_s>(s1->get_point(), *s0));
		}
		else{
			it->second = *s0;
		}
		/*
		if (!parenttest){ 
			parentmap->erase(it);
			parentmap->emplace(pair<Point2D,vertex_s>(s0->get_parent()->get_point(), *s1));
		}*/
		//std::cerr << "else" << s1->get_point() << std::endl;
		s1->set_gvalue(s0->get_gvalue() + meshgrid.getDistance(s0->get_point(), s1->get_point()));
	}
}
vector<Point2D> tstar_mainLoop (SimpleMesh meshgrid, Point2D initpoint, Point2D endpoint){
	vector<Point2D> result;
	vector<vertex_s> open;
	vector<vertex_s> closed;
	vector<Point2D> neighbours;
	vertex_s s_start = vertex_s(initpoint);
	vertex_s s_goal = vertex_s(endpoint);
	vertex_s temp_s;
	vertex_s near_s;
	bool check;

	//unordered_set<vertex_s> vertex_collectionf;
	Point2D point_near_s;
	vector<vertex_s> vectorvertex;
	unordered_map<Point2D,vertex_s> parentmap;
	map<float,vertex_s> openmap;
	s_start.set_gvalue(0);
	s_start.set_parent(&s_start);
	parentmap.emplace(pair<Point2D,vertex_s>(initpoint, s_start));
	//std::cerr << "Mainloop_init" << initpoint << std::endl;
	//parentmap.insert(s_start,s_start);
	openmap.insert(pair<float,vertex_s>(s_start.get_gvalue()+meshgrid.getDistance(s_start.get_point(), s_goal.get_point()), s_start ));
	while (!openmap.empty()){
		std::map<float,vertex_s>::iterator it = openmap.begin();

		temp_s = openmap.begin()->second;
		openmap.erase(openmap.begin());
		//printf("The results: %d , %d \n" ,temp_s.get_point().x,temp_s.get_point().y );

		if (temp_s.get_point() == s_goal.get_point()){


			printf("Path is:");
			vertex_s temporary_vertex;
			Point2D pointholder;
			temporary_vertex = *temp_s.get_parent();
			//cout << temporary_vertex.get_point().x << " , " << temporary_vertex.get_point().y << endl;
			cout << temp_s.get_point().x << " , " << temp_s.get_point().y << endl;
			
			std::unordered_map<Point2D,vertex_s>::iterator it;
			//std::cerr << "temp_s: " << temp_s.get_point() << std::endl;
			it = parentmap.find(temporary_vertex.get_point());
			float distance = 0;
			//it->second.get_point();

			while (true){
				std::unordered_map<Point2D,vertex_s>::iterator it;
				//cout << "iterator test " << temporary_vertex.get_point().x << " , " << temporary_vertex.get_point().y << endl;
	
				it = parentmap.find(temporary_vertex.get_point());
				
				if (it != parentmap.end()){
					//cout << "iterator test " << it->second.get_point().x << " , " << it->second.get_point().y << endl;
					temporary_vertex.set_point(it->second.get_point());
				}
				if (pointholder.x == temporary_vertex.get_point().x and pointholder.y == temporary_vertex.get_point().y){
					break;}
				
				distance = distance + meshgrid.getDistance(temporary_vertex.get_point(), pointholder); 
				
				pointholder = temporary_vertex.get_point();
				printf("The results: %d , %d \n", pointholder.x, pointholder.y);

			}
			
			/*
			printf("%d %d \n", temp_s.get_point().x,temp_s.get_point().y);

			temp_s = *temp_s.get_parent();
			printf("%d %d \n", temp_s.get_point().x,temp_s.get_point().y);

			temp_s = *temp_s.get_parent();
			printf("%d %d \n", temp_s.get_point().x,temp_s.get_point().y);
			*/
			cout << "The total distance for t-star is " << distance << endl;
			return result;
		}
		closed.push_back(temp_s);
		neighbours = meshgrid.getNeighbours(temp_s.get_point());
		while (!neighbours.empty()){


			point_near_s = neighbours.back();
			neighbours.pop_back();
			/*printf("neighbours test");
			printf("%d %d \n", temp_s.get_point().x,temp_s.get_point().y);
			printf("%d %d \n", point_near_s.x,point_near_s.y);
			*/
			near_s.set_point(point_near_s);
			vectorvertex.push_back(near_s);
			//near_s.set_point(point_near_s);
			near_s.set_gvalue(meshgrid.getDistance(near_s.get_point(),temp_s.get_point()));
			//near_s.set_gvalue(meshgrid.getDistance(near_s.get_point(),temp_s.get_point()));
			if ((std::find(closed.begin(), closed.end(),near_s)==closed.end())){
				check = true;
				for (it = openmap.begin(); it != openmap.end(); ++it ){
					if (it->second == near_s){
						check = false;
					}
				}
				if (check == true){
					//printf("changing here");
					near_s.set_gvalue(INT_MAX);
					near_s.set_parent(nullptr);
				}

				tstar_UpdateVertex(&parentmap, s_goal, &temp_s,&near_s,meshgrid, &openmap);
			}
		}
	}
	printf("result not found");
	return result;
}



vector<Point2D> astar_mainLoop (SimpleMesh meshgrid, Point2D initpoint, Point2D endpoint){
	vector<Point2D> result;
	vector<vertex_s> open;
	vector<vertex_s> closed;
	vector<Point2D> neighbours;
	vertex_s s_start = vertex_s(initpoint);
	vertex_s s_goal = vertex_s(endpoint);
	vertex_s temp_s;
	vertex_s near_s;
	bool check;

	//unordered_set<vertex_s> vertex_collectionf;
	Point2D point_near_s;
	vector<vertex_s> vectorvertex;
	unordered_map<Point2D,vertex_s> parentmap;
	map<float,vertex_s> openmap;
	s_start.set_gvalue(0);
	s_start.set_parent(&s_start);
	parentmap.emplace(pair<Point2D,vertex_s>(initpoint, s_start));
	//std::cerr << "Mainloop_init" << initpoint << std::endl;
	//parentmap.insert(s_start,s_start);
	openmap.insert(pair<float,vertex_s>(s_start.get_gvalue()+meshgrid.getDistance(s_start.get_point(), s_goal.get_point()), s_start ));
	while (!openmap.empty()){
		std::map<float,vertex_s>::iterator it = openmap.begin();

		temp_s = openmap.begin()->second;
		openmap.erase(openmap.begin());
		//printf("The results: %d , %d \n" ,temp_s.get_point().x,temp_s.get_point().y );

		if (temp_s.get_point() == s_goal.get_point()){


			printf("Path is:");
			vertex_s temporary_vertex;
			Point2D pointholder;
			temporary_vertex = *temp_s.get_parent();
			//cout << temporary_vertex.get_point().x << " , " << temporary_vertex.get_point().y << endl;
			cout << temp_s.get_point().x << " , " << temp_s.get_point().y << endl;
			
			std::unordered_map<Point2D,vertex_s>::iterator it;
			//std::cerr << "temp_s: " << temp_s.get_point() << std::endl;
			it = parentmap.find(temporary_vertex.get_point());
			float distance = 0;
			//it->second.get_point();

			while (true){
				std::unordered_map<Point2D,vertex_s>::iterator it;
				//cout << "iterator test " << temporary_vertex.get_point().x << " , " << temporary_vertex.get_point().y << endl;
	
				it = parentmap.find(temporary_vertex.get_point());
				
				if (it != parentmap.end()){
					//cout << "iterator test " << it->second.get_point().x << " , " << it->second.get_point().y << endl;
					temporary_vertex.set_point(it->second.get_point());
				}
				if (pointholder.x == temporary_vertex.get_point().x and pointholder.y == temporary_vertex.get_point().y){
					break;}
				distance = distance + meshgrid.getDistance(temporary_vertex.get_point(), pointholder); 
				cout << distance << endl;
				pointholder = temporary_vertex.get_point();
				printf("The results: %d , %d \n", pointholder.x, pointholder.y);

			}
			
			/*
			printf("%d %d \n", temp_s.get_point().x,temp_s.get_point().y);

			temp_s = *temp_s.get_parent();
			printf("%d %d \n", temp_s.get_point().x,temp_s.get_point().y);

			temp_s = *temp_s.get_parent();
			printf("%d %d \n", temp_s.get_point().x,temp_s.get_point().y);
			*/
			cout << "The total distance for astar is " << distance << endl;
			return result;
		}
		closed.push_back(temp_s);
		neighbours = meshgrid.getNeighbours(temp_s.get_point());
		while (!neighbours.empty()){


			point_near_s = neighbours.back();
			neighbours.pop_back();
			/*printf("neighbours test");
			printf("%d %d \n", temp_s.get_point().x,temp_s.get_point().y);
			printf("%d %d \n", point_near_s.x,point_near_s.y);
			*/
			near_s.set_point(point_near_s);
			vectorvertex.push_back(near_s);
			//near_s.set_point(point_near_s);
			near_s.set_gvalue(meshgrid.getDistance(near_s.get_point(),temp_s.get_point()));
			//near_s.set_gvalue(meshgrid.getDistance(near_s.get_point(),temp_s.get_point()));
			if ((std::find(closed.begin(), closed.end(),near_s)==closed.end())){
				check = true;
				for (it = openmap.begin(); it != openmap.end(); ++it ){
					if (it->second == near_s){
						check = false;
					}
				}
				if (check == true){
					//printf("changing here");
					near_s.set_gvalue(INT_MAX);
					//near_s.set_parent(nullptr);
				}

				astar_UpdateVertex(&parentmap, s_goal, &temp_s,&near_s,meshgrid, &openmap);
			}
		}
	}
	printf("result not found");
	return result;
}
bool tstar_lineofsight(vertex_s s0, vertex_s s1, SimpleMesh meshgrid){
	//printf("X value is test lineofsight: %d \n ",s0.x);


	int x0; int y0; int x1; int y1; int dx; int dy; int sx; int sy; int f;



	x0 = s0.x;
	y0 = s0.y;

	x1 = s1.x;
	y1 = s1.y;

	dy = y1-y0;
	dx = x1-x0;

	f = 0;

	if (dy < 0){
		dy = -dy;
		sy = -1;
	}
	else sy = 1;


	if (dx < 0){
		dx = -dx;
		sx = -1;
	}
	else sx = 1;

	if (dx >= dy){
		while (x0 != x1){
			f = f+ dy;
			if (f >= dx){
				if (!meshgrid.isAccessible({x0+((sx-1)/2),y0+((sy-1)/2)})){
					return false;
					}
				y0 = y0+sy;
				f = f-dx;
			}

			if ((f != 0) and (!meshgrid.isAccessible({x0+((sx-1)/2),y0+((sy-1)/2)}))){
				return false;
			}
			if ((dy == 0) and (!meshgrid.isAccessible({x0+((sx-1)/2),y0})) and (!meshgrid.isAccessible({x0+((sx-1)/2),y0-1}))){
				return false;
			}
			x0 = x0 + sx;
			}
		}
	else{
		while(y0 != y1){
			f = f+ dx;
			if (f >= dy){
				if (!meshgrid.isAccessible({x0+((sx-1)/2),y0+((sy-1)/2)})){
					return false;
					}
				x0 = x0+sx;
				f = f-dy;
			}

			if ((f != 0) and (!meshgrid.isAccessible({x0+((sx-1)/2),y0+((sy-1)/2)}))){
				return false;
			}
			if ((dx == 0) and (!meshgrid.isAccessible({x0,y0+((sy-1)/2)})) and (!meshgrid.isAccessible({x0-1,y0+((sy-1)/2)}))){
				return false;
			}
			y0 = y0 + sy;
			}
		}
	return true;
}
