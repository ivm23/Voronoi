#include <iostream>
#include "Voronoi_Diagram.h"
#include "Geom.h"

using namespace std;

int main() {
	
	Point first_point(4,4);
	Point second_point(9,9);
	Point third_point(8,2);
	Point four_point(1,1);
	Point five_point(1,5);
	Voronoi_Diagram vd(first_point);
	
	auto voronoi_cells = vd.get_voronoi_diagram();
	
	auto f_l = voronoi_cells->get_face_list();
	for each (auto face in f_l)
	{
		cout << "FACE " << endl;
		for each (auto edge in face->get_boundary())
		{
			cout << edge->get_origin()->get_vertex_coordinates().x << ' ' << edge->get_origin()->get_vertex_coordinates().y << endl;
			cout << edge->get_twin()->get_origin()->get_vertex_coordinates().x << ' ' << edge->get_twin()->get_origin()->get_vertex_coordinates().y << endl;
		}
	}

	vd.add_new_voronoi_cell(second_point, true);

	cout << "AFTER ADD SECOND POINT\n";
	f_l = voronoi_cells->get_face_list();
	for each (auto face in f_l)
	{
			cout << "FACE: " << face->get_input_point().x << ' ' << face->get_input_point().y << endl;
		for each (auto edge in face->get_boundary())
		{
			cout << edge->get_origin()->get_vertex_coordinates().x << ' ' << edge->get_origin()->get_vertex_coordinates().y << endl;
			cout << edge->get_twin()->get_origin()->get_vertex_coordinates().x << ' ' << edge->get_twin()->get_origin()->get_vertex_coordinates().y << endl;
		}
	}

	second_point.x = 4;
	second_point.y = 6;

	vd.add_new_voronoi_cell(third_point, true);

	cout << "AFTER ADD THIRD POINT\n";
	f_l = voronoi_cells->get_face_list();
	for each (auto face in f_l)
	{
		cout << "FACE: " << face->get_input_point().x << ' ' << face->get_input_point().y << endl;
		for each (auto edge in face->get_boundary())
		{
			cout << edge->get_origin()->get_vertex_coordinates().x << ' ' << edge->get_origin()->get_vertex_coordinates().y << endl;
			cout << edge->get_twin()->get_origin()->get_vertex_coordinates().x << ' ' << edge->get_twin()->get_origin()->get_vertex_coordinates().y << endl;
		}
	}

	second_point.x = 2;
	second_point.y = 8;

	vd.add_new_voronoi_cell(four_point, true);

	cout << "AFTER ADD FOUR POINT\n";
	f_l = voronoi_cells->get_face_list();
	for each (auto face in f_l)
	{
		cout << "FACE: " << face->get_input_point().x << ' ' << face->get_input_point().y << endl;
		for each (auto edge in face->get_boundary())
		{
			cout << edge->get_origin()->get_vertex_coordinates().x << ' ' << edge->get_origin()->get_vertex_coordinates().y << endl;
			cout << edge->get_twin()->get_origin()->get_vertex_coordinates().x << ' ' << edge->get_twin()->get_origin()->get_vertex_coordinates().y << endl;
		}
	}

	vd.add_new_voronoi_cell(five_point, true);

	cout << "AFTER ADD FIVE POINT\n";
	f_l = voronoi_cells->get_face_list();
	for each (auto face in f_l)
	{
		cout << "FACE: " << face->get_input_point().x << ' ' << face->get_input_point().y << endl;
		for each (auto edge in face->get_boundary())
		{
			cout << edge->get_origin()->get_vertex_coordinates().x << ' ' << edge->get_origin()->get_vertex_coordinates().y << endl;
			cout << edge->get_twin()->get_origin()->get_vertex_coordinates().x << ' ' << edge->get_twin()->get_origin()->get_vertex_coordinates().y << endl;
		}
	}



	system("pause");
	return 0;
}