#pragma once
#include <vector>
#include "Point.h"
#include "Const_Values.h"

using namespace std;

Point intersection_lines(pair<Point, Point> line1, pair<Point, Point> line2);
double distance(Point a, Point b);
void get_infPoints(vector<pair<Point, Point>> & boundary_points, vector<pair<Point, Point>>& inf_edges, vector<pair<Point, Point>>& voronoi_diagram_edges);
