#pragma once
#include "Mesh.h"
#include "Straight_Line.h"

bool belong_face(Point input_point, Face* voronoi_mesh);
Point intersection_lines(std::pair<Point, Point> line1, std::pair<Point, Point> line2);
bool check_intersect_point_ray_edge(Point intersect, Point ray_begin_point);
Straight_Line intersection_circles(Point center_point_first, Point center_point_second, double radius_first, double radius_second);
Point intersection_lines(std::pair<Point, Point> line1, Straight_Line line);
bool check_intersect_point_line_edge(Point intersect, std::pair<Point, Point> edge_points);
double squared_distance_between_points(Point point_a, Point point_b);
bool check_order_points(Point first_point, Point second_point); // Who is right? 1 - true, 2 - false
int position_point_relative_straight_line(Point point_stright_line_a, Point point_stright_line_b, Point point);