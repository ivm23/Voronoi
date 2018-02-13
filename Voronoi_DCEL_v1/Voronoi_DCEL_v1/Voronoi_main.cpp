#include <iostream>
#include "Voronoi_Diagram.h"
#include "Geom.h"

using namespace std;

int main() {
	
	Point first_point(1, 2);
	
	Voronoi_Diagram vd;
	
	auto voronoi_cells = vd.get_voronoi_diagram();

	auto vb = voronoi_cells.begin();
	
/*	auto ve = (*vb[0]).get_half_edge_list();
	auto e = ve.begin();
	auto v = (*e)->get_origin();
	auto c = v->get_vertex_coordinates();
	cout << c.x << ' ' << c.y;
	*/
	cout << belong_mesh(first_point, (*vb[0]));	
	system("pause");
	return 0;
}