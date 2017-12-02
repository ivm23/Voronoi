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

int cFrameXl = -20;
int cFrameXr = 20;
int cFrameYu = 20;
int cFrameYd = -20;

bool operator==(const Point& l, const Point& r) {
	return l.x == r.x && l.y == r.y;
}

vector<pair<Point, Point>> draw;
vector<Point> pDraw;
vector<pair<Point, Point>> infDraw;
vector<pair<Point, Point>> pBoundary;

int w = 150, h = 150;

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

Point checkIntersaction(Point a, Point b, Point c, Point d) {
	Point answ{ NULL, NULL };
	double A1 = (b.y - a.y);
	double B1 = (a.x - b.x);
	double C1 = (a.y*b.x - a.x*b.y);

	double A2 = (d.y - c.y);
	double B2 = (c.x - d.x);
	double C2 = (c.y*d.x - c.x*d.y);

	answ.x = -(C1 * B2 - C2 * B1) / (A1 * B2 - A2 * B1);
	answ.y = -(A1*C2 - A2 * C1) / (A1 * B2 - A2 * B1);

	return answ;
}

double distance(Point a, Point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void getInfPoints(vector<pair<Point, Point>> & pBoundary, vector<pair<Point, Point>>& InfPoints)
{
	InfPoints.clear();
	//	cout << "getInfPoints\n";
	for (auto point = pBoundary.begin(); point != pBoundary.end(); ++point) {
		Point intersect{ NULL, NULL };
		Point parabolaVertex{ NULL, NULL };

		double x1 = (*point).first.x;
		double y1 = (*point).first.y;
		double x2 = (*point).second.x;
		double y2 = (*point).second.y;

		double dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

		double p = dist - (x2 - x1);
		double newVertexX = x1 - p / 2.0;
		parabolaVertex.x = newVertexX;
		parabolaVertex.y = y1;

		//intersect
		// x right
		double x = cFrameXr - newVertexX;
		double y = sqrt(2 * p * x);

		if (y2 > y1) {
			y = -y;
		}
		y += y1;

		if (cFrameYd <= y && y <= cFrameYu) {
			intersect.x = x + newVertexX;
			intersect.y = y;
		}
		else {
			// y down
			if (y2 > y1) {
				y = cFrameYd - y1;
			}
			// y up
			else {
				y = cFrameYu - y1;
			}
			x = y * y / (2 * p);

			intersect.x = x + newVertexX;
			intersect.y = y + y1;
		}

		auto pointCheckBoundary = pBoundary.begin();
		double curDist = 100000000000;
		for (auto pointCheckIntersect = InfPoints.begin(); pointCheckIntersect != InfPoints.end(); ++pointCheckIntersect) {
			auto A = (*pointCheckIntersect).first;
			auto B = (*pointCheckIntersect).second;
			auto check = checkIntersaction(parabolaVertex, intersect, A, B);

			if (A.x > B.x) swap(A.x, B.x);
			if (A.y > B.y) swap(A.y, B.y);

			auto C = parabolaVertex;
			auto D = intersect;

			if (C.x > D.x) swap(C.x, D.x);
			if (C.y > D.y) swap(C.y, D.y);

			if (check.x != NULL && (A.x <= check.x && check.x <= B.x && A.y <= check.y && check.y <= B.y) &&
				(C.x <= check.x && check.x <= D.x && C.y <= check.y && check.y <= D.y))
			{

				if (distance(intersect, check) < curDist) {
					curDist = distance(intersect, check);
					intersect.x = check.x;
					intersect.y = check.y;
				}
			}

			A = (*pointCheckIntersect).first;
			B = (*pointCheckBoundary).second;
			check = checkIntersaction(parabolaVertex, intersect, A, B);
			if (A.x > B.x) swap(A.x, B.x);
			if (A.y > B.y) swap(A.y, B.y);

			if (check.x != NULL && (A.x <= check.x && check.x <= B.x && A.y <= check.y && check.y <= B.y) &&
				(C.x <= check.x && check.x <= D.x && C.y <= check.y && check.y <= D.y))
			{
				if (distance(intersect, check) < curDist) {
					curDist = distance(intersect, check);
					intersect.x = check.x;
					intersect.y = check.y;
				}
			}
			++pointCheckBoundary;
		}

		for (auto pointCheckIntersect = draw.begin(); pointCheckIntersect != draw.end(); ++pointCheckIntersect) {
			auto A = (*pointCheckIntersect).first;
			auto B = (*pointCheckIntersect).second;

			auto check = checkIntersaction(parabolaVertex, intersect, A, B);

			if (A.x > B.x) swap(A.x, B.x);
			if (A.y > B.y) swap(A.y, B.y);

			auto C = parabolaVertex;
			auto D = intersect;

			if (C.x > D.x) swap(C.x, D.x);
			if (C.y > D.y) swap(C.y, D.y);

			if (check.x != NULL && (A.x <= check.x && check.x <= B.x && A.y <= check.y && check.y <= B.y) &&
				(C.x <= check.x && check.x <= D.x && C.y <= check.y && check.y <= D.y)
				) {

				if (distance(intersect, check) < curDist) {
					curDist = distance(intersect, check);
					intersect.x = check.x;
					intersect.y = check.y;
				}
			}
		}
		pair<Point, Point> toInfPoints(parabolaVertex, intersect);
		InfPoints.push_back(toInfPoints);

		cout << x2 << ' ' << y2 << " : " << parabolaVertex.x << ' ' << parabolaVertex.y << ' ' << intersect.x << ' ' << intersect.y << endl;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int kol = 0;
	glBegin(GL_LINES);

	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(0, 350);
	glVertex2i(800, 350);

	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(350, 0);
	glVertex2i(350, 600);

	glEnd();
	glBegin(GL_QUADS);

	for (auto point = pDraw.begin(); point != pDraw.end(); ++point) {
		(kol < 8 ? glColor3f(0.0, 1.0, 0.0) : glColor3f(0.0, 0.0, 1.0));

		glVertex2i((*point).x * 10 + w + 200 + 0.01, (*point).y * 10 + h + 200 + 0.01);
		glVertex2i((*point).x * 10 + w + 200 + 0.01, (*point).y * 10 + h + 200 - 0.01);
		glVertex2i((*point).x * 10 + w + 200 - 0.01, (*point).y * 10 + h + 200 + 0.01);
		glVertex2i((*point).x * 10 + w + 200 - 0.01, (*point).y * 10 + h + 200 - 0.01);

		++kol;
		if (kol == 8) break;
	}
	glEnd();

	glBegin(GL_LINES);
	for (auto point = draw.begin(); point != draw.end(); ++point) {
		glColor3f(1.0, 1.0, 1.0);
		glVertex2i((*point).first.x * 10 + w + 200, (*point).first.y * 10 + h + 200);
		glVertex2i((*point).second.x * 10 + w + 200, (*point).second.y * 10 + h + 200);
	}

	cout << "pBoundary\n";
	for (auto point = pBoundary.begin(); point != pBoundary.end(); ++point) {
		cout << (*point).first.x << ' ' << (*point).first.y << ' ' << (*point).second.x << ' ' << (*point).second.y << endl;
	}


	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(cFrameXl * 10 + w + 200, cFrameYu * 10 + h + 200);
	glVertex2i(cFrameXr * 10 + w + 200, cFrameYu * 10 + h + 200);


	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(cFrameXl * 10 + w + 200, cFrameYd * 10 + h + 200);
	glVertex2i(cFrameXr * 10 + w + 200, cFrameYd * 10 + h + 200);


	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(cFrameXl * 10 + w + 200, cFrameYu * 10 + h + 200);
	glVertex2i(cFrameXl * 10 + w + 200, cFrameYd * 10 + h + 200);


	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(cFrameXr * 10 + w + 200, cFrameYu * 10 + h + 200);
	glVertex2i(cFrameXr * 10 + w + 200, cFrameYd * 10 + h + 200);

	vector<pair<Point, Point>> InfPoints;
	vector<pair<Point, Point>> a;
	for (auto point = pBoundary.end() - 1; point != pBoundary.begin(); --point) a.push_back(*point);
	a.push_back(*pBoundary.begin());


	getInfPoints(a, InfPoints);
	auto pointBoundary = a.begin();

	for (auto point = InfPoints.begin(); point != InfPoints.end(); ++point) {
		glColor3f(0.5, 0.5, 0.5);
		glVertex2i((*point).first.x * 10 + w + 200, (*point).first.y * 10 + h + 200);
		glVertex2i((*point).second.x * 10 + w + 200, (*point).second.y * 10 + h + 200);

		glColor3f(0.5, 0.5, 0.5);
		glVertex2i((*point).first.x * 10 + w + 200, (*point).first.y * 10 + h + 200);
		glVertex2i((*pointBoundary).second.x * 10 + w + 200, (*pointBoundary).second.y * 10 + h + 200);

		++pointBoundary;

	}

	glEnd();
	glutSwapBuffers();
}

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


Point FindMidPoint(Point pInputSet1, Point pInputSet2) {
	return Point((pInputSet1.x + pInputSet1.x) / 2, (pInputSet1.y + pInputSet2.y) / 2);
}

int main(int argc, char **argv) {
	// Preparing Input Geometries.
	std::vector<Point> points;

	/*points.push_back(Point(0, 0));
	points.push_back(Point(1, 2));
	points.push_back(Point(3, 1));
	points.push_back(Point(4, 2));
	points.push_back(Point(6, 1));
	points.push_back(Point(2, -3));
	points.push_back(Point(4, -1));
	points.push_back(Point(-1, -1));

	points.push_back(Point(3, 2));
	points.push_back(Point(7, 4));
	points.push_back(Point(5, 0));
	points.push_back(Point(-4, -1));
	points.push_back(Point(-3, 2));
	*/


	points.push_back(Point(0, 1));
	points.push_back(Point(0, 2));

	points.push_back(Point(-4, -1));
	//points.push_back(Point(-3, 2));
	/*points.push_back(Point(3, 3));
	points.push_back(Point(0, 0));
	points.push_back(Point(3, 0));
	points.push_back(Point(0, 3));

	points.push_back(Point(5,5));
	points.push_back(Point(4, -4));
	points.push_back(Point(0, 6));*/



	voronoi_diagram<double> vd;
	construct_voronoi(points.begin(), points.end(), &vd);
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
			Point p = points[index];
			toDraw_point(p);
			printf("Cell #%ud contains a point: (%d, %d).",
				cell_index, x(p), y(p));
			int flag = 0;
			if (it->incident_edge()->is_finite()) {
				cout << it->incident_edge()->vertex0()->x() << ' ' << it->incident_edge()->vertex0()->y() << "\n";
				cout << it->incident_edge()->vertex1()->x() << ' ' << it->incident_edge()->vertex1()->y() << "\n";
			}
			else
			{
				if (it->incident_edge()->vertex0()) {
					boundary.x = it->incident_edge()->vertex0()->x(), boundary.y = it->incident_edge()->vertex0()->y();
					pair<Point, Point> add{ p, boundary };
					pBoundary.push_back(add);
				}
				if (it->incident_edge()->vertex1()) {
					boundary.x = it->incident_edge()->vertex1()->x(), boundary.y = it->incident_edge()->vertex1()->y();
					pair<Point, Point> add{ p, boundary };
					pBoundary.push_back(add);
				}
			}
		}
		++cell_index;
		cout << endl;
	}
	std::cout << std::endl;

	for (auto point = pBoundary.begin(); point != pBoundary.end(); ++point)
	{
		draw_line((*point).first.x, (*point).first.y, (*point).second.x, (*point).second.y);
	}

	cout << "vertex" << endl;
	for (voronoi_diagram<double>::const_vertex_iterator it = vd.vertices().begin();
		it != vd.vertices().end(); ++it) {
		cout << it->x();
		cout << ' ' << it->y() << endl;
		Point toDraw{ it->x(), it->y() };
		toDraw_point(toDraw);
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
						Point vertex0{ edge->vertex0()->x() ,  edge->vertex0()->y() };
						Point vertex1{ edge->vertex1()->x() , edge->vertex1()->y() };
						toDraw_point(vertex0);
						toDraw_point(vertex1);
					}
				}
				else
				{
					auto v0 = edge->vertex0();
					if (v0)
					{
						cout << "Marina style: \n";
						Point pFound{ v0->x(), v0->y() };
						for (auto point = pBoundary.begin(); point != pBoundary.end(); ++point) {
							if ((*point).second == pFound)
							{
								draw_line(v0->x(), v0->y(), (*point).first.x, (*point).first.y);
								Point vertex0{ v0->x() ,  v0->y() };
								Point vertex1{ (*point).first.x ,  (*point).first.y };
								toDraw_point(vertex0);
								pair<Point, Point> toInfDraw(vertex0, vertex1);
								infDraw.push_back(toInfDraw);
							}
						}
						cout << "Marina style end. \n";
					}
				}
			}
			edge = edge->next();
		} while (edge != cell->incident_edge());
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL lesson 1");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutMainLoop();

	//	system("pause");
	return 0;
}
