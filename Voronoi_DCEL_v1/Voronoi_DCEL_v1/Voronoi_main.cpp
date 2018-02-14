#include <iostream>
#include "Voronoi_Diagram.h"
#include "Geom.h"

using namespace std;

int main() {
	
	Point first_point(1,2);
	
	Voronoi_Diagram vd(first_point);
	
	auto voronoi_cells = vd.get_voronoi_diagram();

	auto vb = voronoi_cells.begin();
	
	Point second_point(5,5);
	/*cout << vb[0]->get_input_point().x << ' ' << vb[0]->get_input_point().y << endl;
	auto ve = (*vb[0]).get_half_edge_list();
	auto e = ve.begin();
	auto v = (*e)->get_origin();
	auto c = v->get_vertex_coordinates();
	cout << c.x << ' ' << c.y;
	
	cout << belong_mesh(first_point, (*vb[0])) << endl;*/
	Mesh* mesh_contain_point = vd.point_belong_mesh(first_point);
	cout << (*mesh_contain_point).get_num_vertices() << endl;
	

	auto line = intersection_circles(first_point, second_point, 2, 2);
	cout << line.a << "*x +" << line.b << "*y + " << line.c << " = 0 " << endl;
	auto next_mesh = vd.get_next_mesh_to_change(line, mesh_contain_point);

	system("pause");
	return 0;
}