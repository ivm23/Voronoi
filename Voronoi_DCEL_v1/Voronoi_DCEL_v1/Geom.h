#pragma once
#include "Mesh.h"
#include "Straight_Line.h"

bool belong_mesh(Point input_point, Mesh voronoi_mesh);
Point intersection_lines(std::pair<Point, Point> line1, std::pair<Point, Point> line2);
bool check_intersect_point(Point intersect, Point ray_begin_point);
Straight_Line intersection_circles(Point center_point_first, Point center_point_second, double radius_first, double radius_second);
