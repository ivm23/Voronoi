#include "Check_Belong_inPoints_to_difCells.h"

inline long long area(Point a, Point b, Point c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline bool intersect_1(int a, int b, int c, int d) {
	if (a > b)  swap(a, b);
	if (c > d)  swap(c, d);
	return max(a, c) <= min(b, d);
}

bool intersection_segments(pair<Point, Point> segment1, pair<Point, Point> segment2) {
	return intersect_1(segment1.first.x, segment1.second.x, segment2.first.x, segment2.second.x)
		&& intersect_1(segment1.first.y, segment1.second.y, segment2.first.y, segment2.second.y)
		&& area(segment1.first, segment1.second, segment2.first) * area(segment1.first, segment1.second, segment2.second) <= 0
		&& area(segment2.first, segment2.second, segment1.first) * area(segment2.first, segment2.second, segment1.second) <= 0;
}

Point split_cells(Point pointA, Point pointB, Point common_point) {
	Point midpoint((pointA.x + pointB.x) / 2.0, (pointA.y + pointB.y) / 2.0);
	Point border_frame_right_down(const_frame_right, const_frame_down);
	Point border_frame_right_up(const_frame_right, const_frame_up);
	Point new_infPoint = intersection_lines(pair<Point, Point>(border_frame_right_down, border_frame_right_up), pair<Point, Point>(common_point, midpoint));
	return new_infPoint;

}

void check_belong_inPoints_to_difCells(vector<Point> & inPoints, vector<pair<Point, Point>> & voronoi_diagram_edges, vector<pair<Point, pair<Point, Point>>> & voronoi_diagram_cells) {

	for (auto pointA = inPoints.begin(); pointA != inPoints.end(); ++pointA) {
		for (auto pointB = pointA + 1; pointB != inPoints.end(); ++pointB) {
			pair<Point, Point> segment(*pointA, *pointB);
			bool flag_intersection_segments = false;
			for (auto edge = voronoi_diagram_edges.begin(); edge != voronoi_diagram_edges.end(); ++edge) {
				if (intersection_segments(segment, *edge)) {
					flag_intersection_segments = true;
					break;
				}
			}
			if (!flag_intersection_segments) {
				bool flag_split_cells = false;
				for (auto cellA = voronoi_diagram_cells.begin(); !flag_split_cells && cellA != voronoi_diagram_cells.end(); ++cellA) {
					if ((*cellA).first == (*pointA)) {
						for (auto cellB = voronoi_diagram_cells.begin(); !flag_split_cells && cellB != voronoi_diagram_cells.end(); ++cellB) {
							if ((*cellB).first == (*pointB)) {
								if ((*cellA).second.first == (*cellB).second.first) {
									pair<Point, Point> new_edge = pair<Point, Point>(split_cells(*pointA, *pointB, (*cellA).second.first), (*cellA).second.first);
									pair<Point, pair<Point, Point>> new_cellA((*pointA), new_edge);
									pair<Point, pair<Point, Point>> new_cellB((*pointB), new_edge);
									voronoi_diagram_cells.push_back(new_cellA);
									voronoi_diagram_cells.push_back(new_cellB);
									flag_split_cells = true;
								}
								if ((*cellA).second.second == (*cellB).second.second) {
									pair<Point, Point> new_edge = pair<Point, Point>(split_cells(*pointA, *pointB, (*cellA).second.second), (*cellA).second.second);
									pair<Point, pair<Point, Point>> new_cellA((*pointA), new_edge);
									pair<Point, pair<Point, Point>> new_cellB((*pointB), new_edge);
									voronoi_diagram_cells.push_back(new_cellA);
									voronoi_diagram_cells.push_back(new_cellB);
									flag_split_cells = true;
								}
							}
							if (flag_split_cells) break;
						}
					}
					if (flag_split_cells) break;
				}
			}
		}
	}
}