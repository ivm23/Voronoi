#include <iostream>
#include "Voronoi_Diagram.h"
#include "Geom.h"
#include "Draw.h"

using namespace std;

int main(int argc, char **argv) {
	
	Point first_point(4,3);
	Point second_point(1,9);
	Point third_point(9,2);
	Point four_point(9,8);
	Point five_point(2,2);
	Point six_point(1,1);
	Point seven_point(9,5);
	
	Voronoi_Diagram vd(first_point);
	
	auto voronoi_cells = vd.get_voronoi_diagram();
	
	
	vd.add_new_voronoi_cell(second_point, true);
	vd.add_new_voronoi_cell(third_point, true);
	vd.add_new_voronoi_cell(four_point, true);
	vd.add_new_voronoi_cell(five_point, true);
	vd.add_new_voronoi_cell(six_point, true);
	vd.add_new_voronoi_cell(seven_point, true);

	cout << "AFTER ADD SEVEN POINT\n";
	auto f_l = voronoi_cells->get_face_list();
	f_l = voronoi_cells->get_face_list();
	for each (auto face in f_l)
	{
		cout << "FACE: " << face->get_input_point().x << ' ' << face->get_input_point().y << endl;
		for each (auto edge in face->get_boundary())
		{
			cout << edge->get_origin()->get_vertex_coordinates().x << ' ' << edge->get_origin()->get_vertex_coordinates().y << endl;
			cout << edge->get_twin()->get_origin()->get_vertex_coordinates().x << ' ' << edge->get_twin()->get_origin()->get_vertex_coordinates().y << endl;
			voronoi_diagram_edges.push_back(pair<Point, Point>(edge->get_origin()->get_vertex_coordinates(), edge->get_twin()->get_origin()->get_vertex_coordinates()));
		}
	}

	points.push_back(first_point);
	points.push_back(second_point);
	points.push_back(third_point);
	points.push_back(four_point);
	points.push_back(five_point);
	points.push_back(six_point);
	points.push_back(seven_point);
	

	draw(argc, argv, voronoi_diagram_edges, points);
	system("pause");
	return 0;
}