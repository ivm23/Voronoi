#include <iostream>
#include "Voronoi_Diagram.h"
#include "Geom.h"
#include "Draw.h"
#include <ctime>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	Point array_points[10];
	std::srand(unsigned(std::time(0)));
	int n = 0;
	while (n < 5) {
		Point new_point(std::rand() % 9 + 1, std::rand() % 9 + 1);
		bool isExist = false;
		for (int j = 0; j < n; ++j) {
			if (new_point.equals(array_points[j])) {
				isExist = true;
				break;
			}
		}
		if (!isExist) {
			array_points[n] = new_point;
			points.push_back(new_point);
			cout << new_point.x << ' ' << new_point.y << endl;
			++n;
		}
	}
	cout << "POINTS\n";
	for (int i = 0; i < n; ++i) cout << array_points[i].x << ' ' << array_points[i].y << endl;
	Voronoi_Diagram vd(array_points[0]);
	auto voronoi_cells = vd.get_voronoi_diagram();
	for (int i = 1; i < n; ++i) {
		vd.add_new_voronoi_cell(array_points[i], true);
		cout << "AFTER " << i << " POINT\n";
		auto f_l = voronoi_cells->get_face_list();
		for each (auto face in f_l)
		{
			cout << "FACE: " << face->get_input_point().x << ' ' << face->get_input_point().y << endl;
			for each (auto edge in face->get_boundary())
			{
				cout << edge->get_origin()->get_vertex_coordinates().x << ' ' << edge->get_origin()->get_vertex_coordinates().y << endl;
				cout << edge->get_twin()->get_origin()->get_vertex_coordinates().x << ' ' << edge->get_twin()->get_origin()->get_vertex_coordinates().y << endl;
			}
		}

	}

	auto f_l = voronoi_cells->get_face_list();
	for each (auto face in f_l)
	{
		for each (auto edge in face->get_boundary())
		{
			voronoi_diagram_edges.push_back(pair<Point, Point>(edge->get_origin()->get_vertex_coordinates(), edge->get_twin()->get_origin()->get_vertex_coordinates()));
		}
	}
	draw(argc, argv, voronoi_diagram_edges, points);

	system("pause");
	return 0;
}