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
double ERR = 0.01;
bool check_intersect_point_line_edge(Point intersect, std::pair<Point, Point> edge_points) {
	if (intersect.x == NULL && intersect.y == NULL) return false;
	/*intersect.x = int(intersect.x * err);
	intersect.y = int(intersect.y * err);
	edge_points.first.x = int(edge_points.first.x * err);
	edge_points.first.y = int(edge_points.first.y * err);
	edge_points.second.x = int(edge_points.second.x * err);
	edge_points.second.y = int(edge_points.second.y * err);*/

	if (edge_points.first.x - ERR <= intersect.x && intersect.x <= edge_points.second.x + ERR && edge_points.first.y - ERR <= intersect.y && intersect.y <= edge_points.second.y + ERR) return true;
	if (edge_points.first.x - ERR <= intersect.x && intersect.x <= edge_points.second.x + ERR && edge_points.second.y - ERR <= intersect.y && intersect.y <= edge_points.first.y + ERR) return true;
	if (edge_points.second.x - ERR <= intersect.x && intersect.x <= edge_points.first.x + ERR && edge_points.first.y - ERR <= intersect.y && intersect.y <= edge_points.second.y + ERR) return true;
	if (edge_points.second.x - ERR <= intersect.x && intersect.x <= edge_points.first.x + ERR && edge_points.second.y - ERR <= intersect.y && intersect.y <= edge_points.first.y + ERR) return true;
	return false;
}

bool belong_face(Point input_point, Face* voronoi_face) {
	std::pair<Point, Point> ray_points(input_point, Point(input_point.x + 100, input_point.y));
	std::list<Half_Edge*> edges = (*voronoi_face).get_boundary();
	int count_of_intersect_point = 0;
	bool flag = false;

	for each (auto edge in edges) {
		Vertex * a = (*edge).get_origin();
		Vertex * b = (*(*edge).get_twin()).get_origin();

		std::pair<Point, Point> edge_points((*a).get_vertex_coordinates(), (*b).get_vertex_coordinates());
		Point intersect_point = intersection_lines(ray_points, edge_points);
		
		if (check_intersect_point_line_edge(intersect_point, edge_points) && check_intersect_point_ray_edge(intersect_point, ray_points.first)) {
		if (!intersect_point.equals(edge_points.second)) ++count_of_intersect_point;
		}
	}

	return (count_of_intersect_point % 2 != 0);
}

Straight_Line intersection_circles(Point center_point_first, Point center_point_second, double squared_radius_first, double squared_radius_second) {
	Straight_Line intersection_circles_line (NULL, NULL, NULL);

	intersection_circles_line.a = 2 * (center_point_second.x - center_point_first.x);
	intersection_circles_line.b = 2 * (center_point_second.y - center_point_first.y);
	intersection_circles_line.c = pow(center_point_first.x, 2) - pow(center_point_second.x, 2) + pow(center_point_first.y, 2) - pow(center_point_second.y, 2) - squared_radius_first + squared_radius_second;
	
	return intersection_circles_line;
}

double squared_distance_between_points(Point point_a, Point point_b) {
	return std::pow(point_a.x - point_b.x, 2) + std::pow(point_a.y - point_b.y, 2);
}

bool check_order_points(Point first_point, Point second_point) {
	return first_point > second_point;
}

int position_point_relative_straight_line(Point point_stright_line_a, Point point_stright_line_b, Point point) {
	double d = (point.x - point_stright_line_a.x) * (point.y - point_stright_line_b.y) - (point.x - point_stright_line_b.x)*(point.y - point_stright_line_a.y);
	if (d == 0) return 0;
	return (d > 0 ? 1 : -1);
}