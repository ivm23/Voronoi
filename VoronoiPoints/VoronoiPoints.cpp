//#include <GL/glew.h> // Include the GLEW header file
#include <GL/glut.h> // Include the GLUT header file

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
const int numberOfPoints = 50;
const int razm = 30;
const int cFrameXl = 0;
const int cFrameXr = razm;
const int cFrameYu = razm;
const int cFrameYd = 0;
const int scale = 10;
const int shift = 200;

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
		double curDist = 100000000;
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

		glVertex2i((*point).x * scale + w + shift + 0.01, (*point).y * scale + h + shift + 0.01);
		glVertex2i((*point).x * scale + w + shift + 0.01, (*point).y * scale + h + shift - 0.01);
		glVertex2i((*point).x * scale + w + shift - 0.01, (*point).y * scale + h + shift + 0.01);
		glVertex2i((*point).x * scale + w + shift - 0.01, (*point).y * scale + h + shift - 0.01);

		++kol;
		if (kol == 8) break;
	}
	glEnd();

	glBegin(GL_LINES);
	for (auto point = draw.begin(); point != draw.end(); ++point) {
		glColor3f(1.0, 1.0, 1.0);
		glVertex2i((*point).first.x * scale + w + shift, (*point).first.y * scale + h + shift);
		glVertex2i((*point).second.x * scale + w + shift, (*point).second.y * scale + h + shift);
	}

	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(cFrameXl * scale + w + shift, cFrameYu * scale + h + shift);
	glVertex2i(cFrameXr * scale + w + shift, cFrameYu * scale + h + shift);

	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(cFrameXl * scale + w + shift, cFrameYd * scale + h + shift);
	glVertex2i(cFrameXr * scale + w + shift, cFrameYd * scale + h + shift);

	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(cFrameXl * scale + w + shift, cFrameYu * scale + h + shift);
	glVertex2i(cFrameXl * scale + w + shift, cFrameYd * scale + h + shift);

	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(cFrameXr * scale + w + shift, cFrameYu * scale + h + shift);
	glVertex2i(cFrameXr * scale + w + shift, cFrameYd * scale + h + shift);

	vector<pair<Point, Point>> InfPoints;
	vector<pair<Point, Point>> a;
	for (auto point = pBoundary.end() - 1; point != pBoundary.begin(); --point) a.push_back(*point);
	a.push_back(*pBoundary.begin());

	getInfPoints(a, InfPoints);
	auto pointBoundary = a.begin();

	for (auto point = InfPoints.begin(); point != InfPoints.end(); ++point) {
		glColor3f(0.5, 0.5, 0.5);
		glVertex2i((*point).first.x * scale + w + shift, (*point).first.y * scale + h + shift);
		glVertex2i((*point).second.x * scale + w + shift, (*point).second.y * scale + h + shift);

		glColor3f(0.5, 0.5, 0.5);
		glVertex2i((*point).first.x * scale + w + shift, (*point).first.y * scale + h + shift);
		glVertex2i((*pointBoundary).second.x * scale + w + shift, (*pointBoundary).second.y * scale + h + shift);

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

	vector<Point> points;
	points.clear();
	pBoundary.clear();
	draw.clear();
	infDraw.clear();

	for (int i = 0; i < numberOfPoints; ++i) {
		bool flag = true;
		int x = 0;
		int y = 0;
		while (flag) {
			x = rand() % razm;
			y = rand() % razm;
			flag = false;
			for (auto p = points.begin(); p != points.end(); ++p) if ((*p).x == x && (*p).y == y) {
				flag = true;
				break;
			}
		}
		points.push_back(Point(x, y));
	}

		voronoi_diagram<double> vd;
		construct_voronoi(points.begin(), points.end(), &vd);

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

				int flag = 0;
				if (!(it->incident_edge()->is_finite())) {
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
		}

		for (voronoi_diagram<double>::const_vertex_iterator it = vd.vertices().begin();
			it != vd.vertices().end(); ++it) {
			Point toDraw{ it->x(), it->y() };
			toDraw_point(toDraw);
		}
		for (auto cell = vd.cells().begin(); cell != vd.cells().end(); ++cell) {
			auto edge = cell->incident_edge();
			do {
				if (edge->is_primary())
				{
					if (edge->is_finite())
					{
						if (edge->cell()->source_index() < edge->twin()->cell()->source_index())
						{
							toDraw_line(edge->vertex0()->x(), edge->vertex0()->y(), edge->vertex1()->x(), edge->vertex1()->y());
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
							Point pFound{ v0->x(), v0->y() };
							for (auto point = pBoundary.begin(); point != pBoundary.end(); ++point) {
								if ((*point).second == pFound)
								{
									Point vertex0{ v0->x() ,  v0->y() };
									Point vertex1{ (*point).first.x ,  (*point).first.y };
									toDraw_point(vertex0);
									pair<Point, Point> toInfDraw(vertex0, vertex1);
									infDraw.push_back(toInfDraw);
								}
							}
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
	
	return 0;
}
