#include <iostream> /* Sisend ja väljund */
#include <cstdlib>  /* EXIT_SUCCESS jt konstandid */
#include "tstar_algo.h"
#include <vector>  
using namespace std; /* Nimeruumi valik (selgitatakse praktikumis) */



void tstar_UpdateVertex (int *arrays, int arraylength){
}

void tstar_ComputeCost (int *arrays, int arraylength){
}
void tstar_mainLoop (int *arrays, int arraylength){
}
void tstar_lineofsight(vertex_s s0, vertex_s s1, grid xy){
	int x0; int y0; int x1; int y1; int dx; int dy; int sx; int sy; int f;
	
	x0 = s0.x;
	y0 = s0.y;
	
	x1 = s1.x
	y1 = s1.y
	
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
				
			}
		}
	}
		
}