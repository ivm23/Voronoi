#pragma once
#include <GL/glut.h> // Include the GLUT header file
#include <vector>
#include "Const_Values.h"
#include "Point.h"

using namespace std;

void reshape(int, int);
void display();
void draw_frame();
void draw_axis();

static vector<pair<Point, Point>> voronoi_diagram_edges;
static vector<Point> points;

void draw(int argc, char**argv, vector<pair<Point, Point>> voronoi_diagram_edges, vector<Point>  points);
