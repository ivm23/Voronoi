//#include <GL/glew.h> // Include the GLEW header file
#include <GL/glut.h> // Include the GLUT header file

#include <cstdio>
#include <vector>

#include "boost\polygon\voronoi.hpp"

#include <iostream>

using namespace std;

using boost::polygon::voronoi_builder;
using boost::polygon::voronoi_diagram;
using boost::polygon::x;
using boost::polygon::y;
using boost::polygon::low;
using boost::polygon::high;

struct Point {
	double x;
	double y;

	Point(double a, double b) : x(a), y(b) {}
	friend bool operator==(const Point& l, const Point& r);
};

struct Segment {

	Point p0;
	Point p1;

	Segment(int x1, int y1, int x2, int y2) : p0(x1, y1), p1(x2, y2) {}
};

bool operator==(const Point& l, const Point& r) {
	return l.x == r.x && l.y == r.y;
}

vector<pair<Point, Point>> draw;
vector<Point> pDraw;
vector<pair<Point, Point>> infDraw;
vector<pair<Point, Point>> pBoundary;

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

		template <>
		struct geometry_concept<Segment> {
			typedef segment_concept type;
		};

		template <>
		struct segment_traits<Segment> {
			typedef int coordinate_type;
			typedef Point point_type;

			static inline point_type get(const Segment& segment, direction_1d dir) {
				return dir.to_int() ? segment.p1 : segment.p0;
			}
		};
	}
}




void draw_line(double a, double b, double c, double d) {
	cout << a << ' ' << b << ' ' << c << ' ' << d << endl;
}

void toDraw_line(double a, double b, double c, double d) {
	Point first{ a,b };
	Point second{ c,d };
	pair<Point, Point> toDraw{ first, second };
	draw.push_back(toDraw);
}

void toDraw_point(Point a) {
	pDraw.push_back(a);
}


int main(int argc, char **argv) {
	// Preparing Input Geometries.
	std::vector<Point> points;
	vector<Segment> segments;
	segments.push_back(Segment(-1, 1, 0 , 1));
	segments.push_back(Segment(1, -1, 0, 0 ));
	segments.push_back(Segment(1, 0, 0, 0));
	segments.push_back(Segment(1, -1, 1, 0));

	voronoi_diagram<double> vd;
	construct_voronoi(segments.begin(), segments.end(), &vd);
	{
		printf("Traversing Voronoi graph.\n");
	}

	printf("Number of edges (including secondary) around the Voronoi cells:\n");
	for (voronoi_diagram<double>::const_edge_iterator it = vd.edges().begin();
		it != vd.edges().end(); ++it) {
		std::size_t cnt = it->cell()->color();
		it->cell()->color(cnt + 1);
	}


	unsigned int cell_index = 0;
	for (voronoi_diagram<double>::const_cell_iterator it = vd.cells().begin();
		it != vd.cells().end(); ++it) {
		Point boundary(0, 0);
		int flag = 0;
		if (it->contains_point()) {

			std::size_t index = it->source_index();
			Segment s = segments[index];
			//toDraw_point(p);
			printf("Cell #%ud contains a point: (%d, %d).",
				cell_index, x(s.p0), y(s.p0), x(s.p1), y(s.p1));
			int flag = 0;
			if (it->incident_edge()->is_finite()) {
				cout << it->incident_edge()->vertex0()->x() << ' ' << it->incident_edge()->vertex0()->y() << "\n";
				cout << it->incident_edge()->vertex1()->x() << ' ' << it->incident_edge()->vertex1()->y() << "\n";
			}
			else
			{
				if (it->incident_edge()->vertex0()) {
					boundary.x = it->incident_edge()->vertex0()->x(), boundary.y = it->incident_edge()->vertex0()->y();
				}
				if (it->incident_edge()->vertex1()) {
					boundary.x = it->incident_edge()->vertex1()->x(), boundary.y = it->incident_edge()->vertex1()->y();
				}
			}
		}
		++cell_index;
		cout << endl;
	}
	std::cout << std::endl;

	cout << "vertex" << endl;
	for (voronoi_diagram<double>::const_vertex_iterator it = vd.vertices().begin();
		it != vd.vertices().end(); ++it) {
		cout << it->x();
		cout << ' ' << it->y() << endl;
	}
	cout << "***" << endl;

	for (auto cell = vd.cells().begin(); cell != vd.cells().end(); ++cell) {
		cout << "ceeeeel\n";
		auto edge = cell->incident_edge();
		do {
			cout << "*" << endl;

			if (edge->is_primary())
			{
				if (edge->is_finite())
				{
					if (edge->cell()->source_index() <
						edge->twin()->cell()->source_index())
					{
						draw_line(edge->vertex0()->x(), edge->vertex0()->y(),
							edge->vertex1()->x(), edge->vertex1()->y());
						toDraw_line(edge->vertex0()->x(), edge->vertex0()->y(),
							edge->vertex1()->x(), edge->vertex1()->y());
					}
				}
				else
				{
					auto v0 = edge->vertex0();
					if (v0)
					{

					}
				}
			}
			edge = edge->next();
		} while (edge != cell->incident_edge());
	}
	system("pause");
	return 0;
}
