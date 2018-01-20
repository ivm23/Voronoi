#include "Get_infPoints.h"
#include "Check_Belong_inPoints_to_difCells.h"

/*
	intersection_lines:

	line1 = { (x1, y1); (x2, y2) }
	line2 = { (x3, y3); (x4, y4) }

	Выражаем из системы:
	(y1-y2)*x + (x2-x1)*y + (x1*y1 - x2*y2) = 0
	(y3-y4)*x + (x4-x3)*y + (x3*y3 - x4*y4) = 0
	A, B, C
*/
Point intersection_lines(pair<Point, Point> line1, pair<Point, Point> line2) {

	Point intersection_point { NULL, NULL };
	double A1 = (line1.second.y - line1.first.y);
	double B1 = (line1.first.x - line1.second.x);
	double C1 = (line1.first.y * line1.second.x - line1.first.x * line1.second.y);

	double A2 = (line2.second.y - line2.first.y);
	double B2 = (line2.first.x - line2.second.x);
	double C2 = (line2.first.y * line2.second.x - line2.first.x * line2.second.y);

	intersection_point.x = -(C1 * B2 - C2 * B1) / (A1 * B2 - A2 * B1);
	intersection_point.y = -(A1*C2 - A2 * C1) / (A1 * B2 - A2 * B1);

	return intersection_point;
}

double distance(Point a, Point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
void get_infPoints(vector<pair<Point, Point>> & boundary_points, vector<pair<Point, Point>>& inf_edges, vector<pair<Point, Point>>& voronoi_diagram_edges) {

	inf_edges.clear();

	for (auto pair_pointIn_pointBoundary = boundary_points.begin(); pair_pointIn_pointBoundary!= boundary_points.end(); ++pair_pointIn_pointBoundary) {
		Point intersect_point{ NULL, NULL };
		Point parabola_vertex_point{ NULL, NULL };

		// восстановление вершины параболы y^2 = 2 * p * x
		double pointIn_x = (*pair_pointIn_pointBoundary).first.x;
		double pointIn_y = (*pair_pointIn_pointBoundary).first.y;
		double pointBoundary_x = (*pair_pointIn_pointBoundary).second.x;
		double pointBoundary_y = (*pair_pointIn_pointBoundary).second.y;

		double dist_pointIn_pointBoundary = sqrt((pointIn_x - pointBoundary_x) * (pointIn_x - pointBoundary_x) + (pointIn_y - pointBoundary_y) * (pointIn_y - pointBoundary_y));

		double p = dist_pointIn_pointBoundary - (pointBoundary_x - pointIn_x);
		double new_vertex_x = pointIn_x - p / 2.0;
		parabola_vertex_point.x = new_vertex_x;
		parabola_vertex_point.y = pointIn_y;

		// пересечение с рамкой
		double x = const_frame_right - new_vertex_x;
		double y = sqrt(2 * p * x);

		if (pointBoundary_y > pointIn_y) {
			y = -y;
		}
		y += pointIn_y;

		if (const_frame_down <= y && y <= const_frame_up) {
			intersect_point.x = x + new_vertex_x;
			intersect_point.y = y;
		}
		else {
			if (pointBoundary_y > pointIn_y) {
				y = const_frame_down - pointIn_y;
			}
			else {
				y = const_frame_up - pointIn_y;
			}

			x = y * y / (2 * p);

			intersect_point.x = x + new_vertex_x;
			intersect_point.y = y + pointIn_y;
		}

		// избавляемся от новых (полученных в процессе данного метода) дуг внутри парабол
		auto point_check_boundary = boundary_points.begin();
		double cur_dist = MAX_DIST;
		for (auto exist_infEdge = inf_edges.begin(); exist_infEdge != inf_edges.end(); ++exist_infEdge) {
			auto exist_infEdge_pointA = (*exist_infEdge).first;
			auto exist_infEdge_pointB = (*exist_infEdge).second;
			auto point_check_intersection = intersection_lines(pair<Point,Point> (parabola_vertex_point, intersect_point) , *exist_infEdge);
			
			if (intersection_segments(pair<Point, Point>(parabola_vertex_point, intersect_point), *exist_infEdge)) {
				point_check_intersection = intersection_lines(pair<Point, Point>(parabola_vertex_point, intersect_point), *exist_infEdge);
				intersect_point.x = point_check_intersection.x;
				intersect_point.y = point_check_intersection.y;
			}
		
			exist_infEdge_pointA = (*exist_infEdge).first;
			exist_infEdge_pointB = (*point_check_boundary).second;

			if (intersection_segments(pair<Point, Point>(parabola_vertex_point, intersect_point), pair<Point, Point>(exist_infEdge_pointA, exist_infEdge_pointB))) {
				point_check_intersection = intersection_lines(pair<Point, Point>(parabola_vertex_point, intersect_point), pair<Point, Point>(exist_infEdge_pointA, exist_infEdge_pointB));
				intersect_point.x = point_check_intersection.x;
				intersect_point.y = point_check_intersection.y;
			}
			++point_check_boundary;
		}

		for (auto pointCheckIntersect = voronoi_diagram_edges.begin(); pointCheckIntersect != voronoi_diagram_edges.end(); ++pointCheckIntersect) {
			auto A = (*pointCheckIntersect).first;
			auto B = (*pointCheckIntersect).second;
			
			if (intersection_segments(pair<Point, Point>(parabola_vertex_point, intersect_point), pair<Point, Point>(A, B))) {
				auto point_check_intersection = intersection_lines(pair<Point, Point>(parabola_vertex_point, intersect_point), pair<Point, Point>(A, B));
				intersect_point.x = point_check_intersection.x;
				intersect_point.y = point_check_intersection.y;
			}
		}
		pair<Point, Point> toInfPoints(parabola_vertex_point, intersect_point);
		inf_edges.push_back(toInfPoints);
	}

}

