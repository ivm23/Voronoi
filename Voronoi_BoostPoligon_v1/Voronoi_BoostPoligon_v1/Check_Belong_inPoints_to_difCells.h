#pragma once
#include <vector>
#include "Point.h"
#include <algorithm>
#include "Get_infPoints.h"

using namespace std;


bool intersection_segments(pair<Point, Point> segment1, pair<Point, Point> segment2);
void check_belong_inPoints_to_difCells(vector<Point> & inPoints, vector<pair<Point, Point>> & voronoi_diagram_edges, vector<pair<Point, pair<Point, Point>>> & voronoi_diagram_cells);