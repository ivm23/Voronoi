#include <cstdio>
#include <iostream>
#include <ctime>
#include "boost\polygon\voronoi.hpp"
#include "Get_infPoints.h"
#include "Draw.h"
#include "Check_Belong_inPoints_to_difCells.h"

using namespace std;

using boost::polygon::voronoi_builder;
using boost::polygon::voronoi_diagram;
using boost::polygon::x;
using boost::polygon::y;
using boost::polygon::low;
using boost::polygon::high;

vector<pair<Point, Point>> boundary_points; // (inPoint, boundaryPoint)
vector<pair<Point, pair<Point, Point>>> voronoi_diagram_cells;
namespace boost {
	namespace polygon {

		template <>
		struct geometry_concept<Point> {
			typedef point_concept type;
		};

		template <>
		struct point_traits<Point> {
			typedef int coordinate_type;

			static inline coordinate_type get(
				const Point& point, orientation_2d orient) {
				return (orient == HORIZONTAL) ? point.x : point.y;
			}
		};
	}
}

int main(int argc, char **argv) {

	vector<Point> points;
	points.clear();
	boundary_points.clear();	
	/*srand(time(0));
	for (int i = 0; i < numberOfPoints; ++i) {
		bool flag = true;
		int x = 0;
		int y = 0;
		while (flag) {
			x = rand() % size_frame;
			y = rand() % size_frame;
			flag = false;
			for (auto p = points.begin(); p != points.end(); ++p) if ((*p).x == x && (*p).y == y) {
				flag = true;
				break;
			}
		}
		points.push_back(Point(x, y));
	}*/
	points.push_back(Point(4, 5));
	points.push_back(Point(9, 9));
	//points.push_back(Point(9, 1));
	points.push_back(Point(2, 2));
	
	/*points.push_back(Point(1, 1));
	points.push_back(Point(1, 5));
	points.push_back(Point(5, 5));
	points.push_back(Point(5, 1));*/
	voronoi_diagram<double> built_voronoi_diagram;

	construct_voronoi(points.begin(), points.end(), &built_voronoi_diagram);
	
	vector<pair<Point, Point>> voronoi_diagram_edges; // добавим внутренние ребра диаграммы Вороного, далее будем проверять пересечения с ними
	voronoi_diagram_edges.clear();
	for (auto cell = built_voronoi_diagram.cells().begin(); cell != built_voronoi_diagram.cells().end(); ++cell) {
		auto edge = cell->incident_edge();
		do {
			std::size_t index = cell->source_index(); // получаем исходные точки (входные данные)
			Point p = points[index];

			if (edge->is_primary()) {
				if (edge->is_finite()) {
					if (edge->cell()->source_index() < edge->twin()->cell()->source_index()) {
						Point vertexA(edge->vertex0()->x(), edge->vertex0()->y());
						Point vertexB(edge->vertex1()->x(), edge->vertex1()->y());
						pair<Point, Point> voronoi_edge(vertexA, vertexB);
						voronoi_diagram_edges.push_back(voronoi_edge);
						pair<Point, pair<Point, Point>> point_edge(p, voronoi_edge);
						voronoi_diagram_cells.push_back(point_edge);
					}
				}
			}
			Point boundary(0, 0);
			
			if (!(edge->is_finite()) && edge->next() != cell->incident_edge()) { // если ребро не конечное
				if (edge->vertex0()) { // если 0-ая вершина конечна, то добавим ее в список граничных точек 
					boundary.x = edge->vertex0()->x();
					boundary.y = edge->vertex0()->y();
					pair<Point, Point> new_boundary_pair{ p, boundary };
					boundary_points.push_back(new_boundary_pair);
				}
				if (edge->vertex1()) { // аналогично для второй вершины
					boundary.x = edge->vertex1()->x();
					boundary.y = edge->vertex1()->y();
					pair<Point, Point> add(p, boundary);
					boundary_points.push_back(add);
				}
			}
			edge = edge->next();
		} while (edge != cell->incident_edge());
	}

	vector<pair<Point, Point>> inf_edges;
	vector<pair<Point, Point>> rev_boundary_points;
	for (auto point = boundary_points.end() - 1; point != boundary_points.begin(); --point) rev_boundary_points.push_back(*point);
	rev_boundary_points.push_back(*boundary_points.begin());

	get_infPoints(rev_boundary_points, inf_edges, voronoi_diagram_edges);

	auto edge_boundary = rev_boundary_points.begin();
	for (auto edge = inf_edges.begin(); edge != inf_edges.end(); ++edge) {
		pair<Point, pair<Point, Point>> point_edge((*edge_boundary).first, *edge);
		voronoi_diagram_cells.push_back(point_edge);

		Point vertexA((*edge).first);
		Point vertexB((*edge_boundary).second);
		pair<Point, Point> new_edge(vertexA, vertexB);
		pair<Point, pair<Point, Point>> new_point_edge((*edge_boundary).first, new_edge);
		voronoi_diagram_cells.push_back(new_point_edge);
		++edge_boundary;
	}
	cout << "InPoints \n";
	for (auto point = points.begin(); point != points.end(); ++point) {
		cout << (*point).x << ' ' << (*point).y << endl;
	}
	cout << "Voronoi diagram\n";

	for (auto edge = voronoi_diagram_cells.begin(); edge != voronoi_diagram_cells.end(); ++edge) {
		cout << "Point: " << (*edge).first.x << ' ' << (*edge).first.y << " edge: " << (*edge).second.first.x << ' ' << (*edge).second.first.y << ' ' << (*edge).second.second.x << ' ' << (*edge).second.second.y << endl;
	}
	
	voronoi_diagram_edges.clear();
	for (auto edge = voronoi_diagram_cells.begin(); edge != voronoi_diagram_cells.end(); ++edge) {
		voronoi_diagram_edges.push_back((*edge).second);
	}
	
	check_belong_inPoints_to_difCells(points, voronoi_diagram_edges, voronoi_diagram_cells);
	voronoi_diagram_edges.clear();
	for (auto edge = voronoi_diagram_cells.begin(); edge != voronoi_diagram_cells.end(); ++edge) {
		voronoi_diagram_edges.push_back((*edge).second);
	}

	draw(argc, argv, voronoi_diagram_edges, points);
	system("pause");
	return 0;
}
