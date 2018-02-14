#include "Geom.h"
#include "Mesh.h"
#include <math.h>

Point intersection_lines(std::pair<Point, Point> line1, std::pair<Point, Point> line2) {
	Point intersection_point{ NULL, NULL };
	double A1 = (line1.second.y - line1.first.y);
	double B1 = (line1.first.x - line1.second.x);
	double C1 = (line1.first.y * line1.second.x - line1.first.x * line1.second.y);

	double A2 = (line2.second.y - line2.first.y);
	double B2 = (line2.first.x - line2.second.x);
	double C2 = (line2.first.y * line2.second.x - line2.first.x * line2.second.y);

	if (A1 * B2 - A2 * B1 == 0) return intersection_point;

	intersection_point.x = -(C1 * B2 - C2 * B1) / (A1 * B2 - A2 * B1);
	intersection_point.y = -(A1 * C2 - A2 * C1) / (A1 * B2 - A2 * B1);

	return intersection_point;
}

Point intersection_lines(std::pair<Point, Point> line1, Straight_Line line) {
	Point intersection_point{ NULL, NULL };
	double A1 = (line1.second.y - line1.first.y);
	double B1 = (line1.first.x - line1.second.x);
	double C1 = (line1.first.y * line1.second.x - line1.first.x * line1.second.y);

	double A2 = line.a;
	double B2 = line.b;
	double C2 = line.c;

	if (A1 * B2 - A2 * B1 == 0) return intersection_point;

	intersection_point.x = -(C1 * B2 - C2 * B1) / (A1 * B2 - A2 * B1);
	intersection_point.y = -(A1 * C2 - A2 * C1) / (A1 * B2 - A2 * B1);

	return intersection_point;
}

bool check_intersect_point_ray_edge(Point intersect, Point ray_begin_point) {
	return (intersect.x == NULL && intersect.y == NULL || !(intersect.x > ray_begin_point.x) ? false : true);
}

bool check_intersect_point_line_edge(Point intersect, std::pair<Point, Point> edge_points) {
	if (intersect.x == NULL && intersect.y == NULL) return false;
	if (edge_points.first.x <= intersect.x && intersect.x <= edge_points.second.x && edge_points.first.y <= intersect.y && intersect.y <= edge_points.second.y) return true;
	if (edge_points.first.x <= intersect.x && intersect.x <= edge_points.second.x && edge_points.second.y <= intersect.y && intersect.y <= edge_points.first.y) return true;
	if (edge_points.second.x <= intersect.x && intersect.x <= edge_points.first.x && edge_points.first.y <= intersect.y && intersect.y <= edge_points.second.y) return true;
	if (edge_points.second.x <= intersect.x && intersect.x <= edge_points.first.x && edge_points.second.y <= intersect.y && intersect.y <= edge_points.first.y) return true;
	return false;
}

bool belong_mesh(Point input_point, Mesh voronoi_mesh) {
	std::pair<Point, Point> ray_points(Point(input_point.x + 1, input_point.y), input_point);
	std::vector<Face*> face_list = voronoi_mesh.get_face_list();
	Face* face = face_list[0];
	std::list<Half_Edge*> edges = (*face).get_boundary();

	int count_of_intersect_point = 0;

	for each (auto edge in edges) {
		Vertex * a = (*edge).get_origin();
		Vertex * b = (*(*edge).get_twin()).get_origin();

		std::pair<Point, Point> edge_points((*a).get_vertex_coordinates(), (*b).get_vertex_coordinates());
		Point intersect_point = intersection_lines(ray_points, edge_points);

		if (check_intersect_point_ray_edge(intersect_point, ray_points.first)) ++count_of_intersect_point;
	}

	return (count_of_intersect_point % 2 != 0);
}

Straight_Line intersection_circles(Point center_point_first, Point center_point_second, double radius_first, double radius_second) {
	Straight_Line intersection_circles_line (NULL, NULL, NULL);

	intersection_circles_line.a = 2 * (center_point_second.x - center_point_first.x);
	intersection_circles_line.b = 2 * (center_point_second.y - center_point_first.y);
	intersection_circles_line.c = pow(center_point_first.x, 2) - pow(center_point_second.x, 2) + pow(center_point_first.y, 2) - pow(center_point_second.y, 2) - pow(radius_first, 2) + pow(radius_second, 2);
	
	return intersection_circles_line;
}