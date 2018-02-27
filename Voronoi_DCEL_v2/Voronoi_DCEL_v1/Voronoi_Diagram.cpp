#include"Voronoi_Diagram.h"
#include <iostream>

Voronoi_Diagram::Voronoi_Diagram(Point first_input_point) {
	voronoi_diagram = new Mesh;
	first_intersect.first = NULL;
	first_intersect.second.x = NULL;
	first_intersect.second.y = NULL;

	Half_Edge* frame_left_half_edge = (*voronoi_diagram).create_half_edge();
	Half_Edge* frame_left_half_edge_twin = (*voronoi_diagram).create_half_edge();

	Half_Edge* frame_up_half_edge = (*voronoi_diagram).create_half_edge();
	Half_Edge* frame_up_half_edge_twin = (*voronoi_diagram).create_half_edge();

	Half_Edge* frame_right_half_edge = (*voronoi_diagram).create_half_edge();
	Half_Edge* frame_right_half_edge_twin = (*voronoi_diagram).create_half_edge();

	Half_Edge* frame_down_half_edge = (*voronoi_diagram).create_half_edge();
	Half_Edge* frame_down_half_edge_twin = (*voronoi_diagram).create_half_edge();

	Vertex* frame_left_down_point = (*voronoi_diagram).create_vertex(FRAME_LEFT_DOWN);
	Vertex* frame_left_up_point = (*voronoi_diagram).create_vertex(FRAME_LEFT_UP);
	Vertex* frame_right_down_point = (*voronoi_diagram).create_vertex(FRAME_RIGHT_DOWN);
	Vertex* frame_right_up_point = (*voronoi_diagram).create_vertex(FRAME_RIGHT_UP);

	Face* face = (*voronoi_diagram).create_face(first_input_point);

	(*frame_left_half_edge).set_origin(frame_left_down_point);
	(*frame_up_half_edge).set_origin(frame_left_up_point);
	(*frame_right_half_edge).set_origin(frame_right_up_point);
	(*frame_down_half_edge).set_origin(frame_right_down_point);

	(*frame_left_half_edge_twin).set_origin(frame_left_up_point);
	(*frame_up_half_edge_twin).set_origin(frame_right_up_point);
	(*frame_right_half_edge_twin).set_origin(frame_right_down_point);
	(*frame_down_half_edge_twin).set_origin(frame_left_down_point);

	(*frame_left_half_edge).set_twin(frame_left_half_edge_twin);
	(*frame_up_half_edge).set_twin(frame_up_half_edge_twin);
	(*frame_right_half_edge).set_twin(frame_right_half_edge_twin);
	(*frame_down_half_edge).set_twin(frame_down_half_edge_twin);

	(*frame_left_half_edge_twin).set_twin(frame_left_half_edge);
	(*frame_up_half_edge_twin).set_twin(frame_up_half_edge);
	(*frame_right_half_edge_twin).set_twin(frame_right_half_edge);
	(*frame_down_half_edge_twin).set_twin(frame_down_half_edge);

	(*frame_left_half_edge).set_next(frame_up_half_edge);
	(*frame_up_half_edge).set_next(frame_right_half_edge);
	(*frame_right_half_edge).set_next(frame_down_half_edge);
	(*frame_down_half_edge).set_next(frame_left_half_edge);

	(*frame_left_half_edge_twin).set_next(frame_up_half_edge_twin);
	(*frame_up_half_edge_twin).set_next(frame_right_half_edge_twin);
	(*frame_right_half_edge_twin).set_next(frame_down_half_edge_twin);
	(*frame_down_half_edge_twin).set_next(frame_left_half_edge_twin);


	(*frame_left_half_edge).set_prev(frame_down_half_edge);
	(*frame_down_half_edge).set_prev(frame_right_half_edge);
	(*frame_right_half_edge).set_prev(frame_up_half_edge);
	(*frame_up_half_edge).set_prev(frame_left_half_edge);

	(*frame_left_half_edge_twin).set_prev(frame_down_half_edge_twin);
	(*frame_down_half_edge_twin).set_prev(frame_right_half_edge_twin);
	(*frame_right_half_edge_twin).set_prev(frame_up_half_edge_twin);
	(*frame_up_half_edge_twin).set_prev(frame_left_half_edge_twin);

	std::list<Half_Edge*> boundary;
	boundary.push_back(frame_left_half_edge);
	boundary.push_back(frame_up_half_edge);
	boundary.push_back(frame_right_half_edge);
	boundary.push_back(frame_down_half_edge);

	(*face).set_boundary(boundary);

	(*frame_left_half_edge).set_face(face);
	(*frame_up_half_edge).set_face(face);
	(*frame_right_half_edge).set_face(face);
	(*frame_down_half_edge).set_face(face);

	(*frame_left_half_edge_twin).set_face(NULL);
	(*frame_up_half_edge_twin).set_face(NULL);
	(*frame_right_half_edge_twin).set_face(NULL);
	(*frame_down_half_edge_twin).set_face(NULL);

	(*frame_left_down_point).set_incident_half_edge(frame_left_half_edge);
	(*frame_left_up_point).set_incident_half_edge(frame_up_half_edge);
	(*frame_right_up_point).set_incident_half_edge(frame_right_half_edge);
	(*frame_right_down_point).set_incident_half_edge(frame_down_half_edge);
};




Face* Voronoi_Diagram::point_belong_face(Point point) {
	for each (auto face in voronoi_diagram->get_face_list())
	{
		if (belong_face(point, face)) return face;
	}
}
void Voronoi_Diagram::finish_boundary(Face * face, std::list<Half_Edge*> &boundary) {
	boundary.reverse();
	auto first_edge = boundary.back();
	auto end_edge = boundary.front();
	if (first_edge->get_twin()->get_origin()->get_vertex_coordinates() != end_edge->get_origin()->get_vertex_coordinates()) {
		Half_Edge * new_half_edge = NULL;
		Half_Edge * new_half_edge_twin = NULL;

		Half_Edge * prev_new_half_edge = first_edge;

		Vertex * new_vertex = NULL;
		Vertex * prev_new_vertex = first_edge->get_twin()->get_origin();
		Point point;
		int flag = 0;
		while (!(first_edge->get_twin()->get_origin()->get_vertex_coordinates().equals(end_edge->get_origin()->get_vertex_coordinates()))) {
			double x = first_edge->get_twin()->get_origin()->get_vertex_coordinates().x;
			double y = first_edge->get_twin()->get_origin()->get_vertex_coordinates().y;

			double x_end = end_edge->get_origin()->get_vertex_coordinates().x;
			double y_end = end_edge->get_origin()->get_vertex_coordinates().y;
			if (x == 0 && (flag == 4 || flag == 0)) {
				flag = 2;
				if (x_end == 0) {
					point.y = y_end;
				}
				else {
					point.y = 10;
				}

				point.x = 0;
			}
			else
				if (x == 10 && (flag == 1 || flag == 0)) {
					flag = 3;
					if (x_end == 10) {
						point.y = y_end;
					}
					else {
						point.y = 0;
					}
					point.x = 10;

				}
				else
					if (y == 0 && (flag == 3 || flag == 0)) {
						flag = 4;
						if (y_end == 0) {
							point.x = x_end;
						}
						else {
							point.x = 0;
						}
						point.y = 0;
					}
					else
						if (y == 10 && (flag == 2 || flag == 0)) {
							flag = 1;
							if (y_end == 10) {
								point.x = x_end;
							}
							else {
								point.x = 10;
							}
							point.y = 10;
						}
			new_vertex = voronoi_diagram->create_vertex(point);
			new_vertex->set_incident_half_edge(new_half_edge_twin);

			new_half_edge = voronoi_diagram->create_half_edge();
			new_half_edge_twin = voronoi_diagram->create_half_edge();

			prev_new_half_edge->set_next(new_half_edge);
			prev_new_half_edge->get_twin()->set_prev(new_half_edge_twin);

			new_half_edge->set_origin(prev_new_vertex);
			new_half_edge->set_prev(prev_new_half_edge);
			new_half_edge->set_twin(new_half_edge_twin);
			new_half_edge->set_face(face);

			new_half_edge_twin->set_origin(new_vertex);
			new_half_edge_twin->set_next(prev_new_half_edge->get_twin());
			new_half_edge_twin->set_twin(new_half_edge);
			new_half_edge_twin->set_face(NULL);

			boundary.push_back(new_half_edge);
			first_edge = new_half_edge;
			prev_new_half_edge = new_half_edge;
			prev_new_vertex = new_vertex;
		}

		prev_new_half_edge->set_next(end_edge);
		prev_new_half_edge->get_twin()->set_prev(end_edge->get_twin());
		//boundary.back()->set_next(boundary.front());
		//auto next_for_front = boundary.front();
		//next_for_front++;
		//boundary.front()->set_next(next_for_front);

		face->set_boundary(boundary);
	}

}

bool equals(Face * face_a, Face * face_b) {
	bool is_other_edge = false;
	if (face_a->get_boundary().size() != face_b->get_boundary().size() || face_a->get_input_point() != face_b->get_input_point()) return false;

	Half_Edge* edge_of_boundary = face_a->get_boundary().front();
	Half_Edge* edge_of_other_boundary = face_b->get_boundary().front();

	while (edge_of_boundary != face_a->get_boundary().back()) {
		if (edge_of_boundary->get_origin()->get_vertex_coordinates() != edge_of_other_boundary->get_origin()->get_vertex_coordinates()) {
			return false;
		}
		edge_of_boundary = edge_of_boundary->get_next();
		edge_of_other_boundary = edge_of_other_boundary->get_next();
	}
	return (edge_of_boundary->get_origin()->get_vertex_coordinates() == edge_of_other_boundary->get_origin()->get_vertex_coordinates() ? true : false);
}

std::list<std::pair<Half_Edge*, Point>> Voronoi_Diagram::get_list_face(Face* begin, Point add_point) {
	std::list<std::pair<Half_Edge*, Point>> list_face;

	Point face_point = begin->get_input_point();

	double squared_radius = squared_distance_between_points(add_point, face_point);
	Straight_Line circle_intersection_line = intersection_circles(add_point, face_point, squared_radius, squared_radius);

	Point first_intersect_point(NULL, NULL);
	Point second_intersect_point(NULL, NULL);

	Half_Edge* half_edge_for_first_intersect_point = NULL;
	Half_Edge* half_edge_for_second_intersect_point = NULL;

	bool is_second_intersect_point = false;
	int is_end_of_cycle = 0;
	auto edge = begin->get_boundary().front();
	while (is_end_of_cycle != 2)
	{
		std::pair<Point, Point> edge_points(edge->get_origin()->get_vertex_coordinates(), edge->get_twin()->get_origin()->get_vertex_coordinates());
		Point intersect_point = intersection_lines(edge_points, circle_intersection_line);

		if (check_intersect_point_line_edge(intersect_point, edge_points)) {
			if (!is_second_intersect_point) {
				first_intersect_point = intersect_point;
				half_edge_for_first_intersect_point = edge;
				is_second_intersect_point = true;
			}
			else {
				second_intersect_point = intersect_point;
				half_edge_for_second_intersect_point = edge;
				break;
			}
		}
		edge = edge->get_next();
		if (is_end_of_cycle == 1) is_end_of_cycle = 2;
		if (edge == begin->get_boundary().back()) is_end_of_cycle = 1;
	}

	if (position_point_relative_straight_line(first_intersect_point, second_intersect_point, add_point) < 0) {
		std::swap(first_intersect_point, second_intersect_point);
		std::swap(half_edge_for_first_intersect_point, half_edge_for_second_intersect_point);
	}
	list_face.push_front(std::pair<Half_Edge*, Point>(half_edge_for_first_intersect_point, first_intersect_point));
	list_face.push_back(std::pair<Half_Edge*, Point>(half_edge_for_second_intersect_point, second_intersect_point));

	while (!second_intersect_point.equals(first_intersect_point)) {
		Face* next_face = half_edge_for_first_intersect_point->get_twin()->get_face();
		if (next_face != NULL) {
			face_point = next_face->get_input_point();

			double squared_radius = squared_distance_between_points(add_point, face_point);
			Straight_Line circle_intersection_line = intersection_circles(add_point, face_point, squared_radius, squared_radius);

			for each (auto edge in next_face->get_boundary()) {
				std::pair<Point, Point> edge_points(edge->get_origin()->get_vertex_coordinates(), edge->get_twin()->get_origin()->get_vertex_coordinates());
				Point intersect_point = intersection_lines(edge_points, circle_intersection_line);

				if (check_intersect_point_line_edge(intersect_point, edge_points)) {
					if (!intersect_point.equals(first_intersect_point)) {
						half_edge_for_first_intersect_point = edge;
					}
					list_face.push_front(std::pair<Half_Edge*, Point>(edge, intersect_point));
				}
			}

		}
		else break;
	}

	while (!second_intersect_point.equals(first_intersect_point)) {
		Face* next_face = half_edge_for_second_intersect_point->get_twin()->get_face();
		if (next_face != NULL) {
			face_point = next_face->get_input_point();

			double squared_radius = squared_distance_between_points(add_point, face_point);
			Straight_Line circle_intersection_line = intersection_circles(add_point, face_point, squared_radius, squared_radius);

			for each (auto edge in next_face->get_boundary()) {
				std::pair<Point, Point> edge_points(edge->get_origin()->get_vertex_coordinates(), edge->get_twin()->get_origin()->get_vertex_coordinates());
				Point intersect_point = intersection_lines(edge_points, circle_intersection_line);

				if (check_intersect_point_line_edge(intersect_point, edge_points)) {
					
					if (!intersect_point.equals(second_intersect_point)) {
						half_edge_for_second_intersect_point = edge;
					}
					list_face.push_back(std::pair<Half_Edge*, Point>(edge, intersect_point));
				}
			}

		}
		else break;
	}
	return list_face;
}

bool checkInLine(Point a, Point b, Point inLine) {
	return (-0.05 <= (inLine.x - a.x) * (b.y - a.y) - (inLine.y - a.y)*(b.x - a.x) && (inLine.x - a.x) * (b.y - a.y) - (inLine.y - a.y)*(b.x - a.x) <= 0.05 && (a.x <= inLine.x && inLine.x <= b.x || b.x <= inLine.x && inLine.x <= a.x));
}


void Voronoi_Diagram::add_new_voronoi_cell(Point point_to_add, bool f) {

	Face* face_with_point_to_add = point_belong_face(point_to_add);

	Face * new_face_for_add_point = voronoi_diagram->create_face(point_to_add);
	Point face_point = face_with_point_to_add->get_input_point();

	std::list<std::pair<Half_Edge *, Point>> next_half_edge = get_list_face(face_with_point_to_add, point_to_add);
	auto pair_edge_point = next_half_edge.begin();

	Vertex * first_vertex = voronoi_diagram->create_vertex(pair_edge_point->second);
	Half_Edge * new_half_edge = voronoi_diagram->create_half_edge();
	Half_Edge * new_half_edge_twin = voronoi_diagram->create_half_edge();

	Half_Edge * prev_half_edge = NULL;
	Half_Edge * prev_half_edge_twin = NULL;

	while (pair_edge_point != next_half_edge.end()) {
		Face* currentFace = pair_edge_point->first->get_face();
		Point currentPoint = currentFace->get_input_point();
		auto boundary = currentFace->get_boundary();
		auto edge = boundary.front();

		Point first_point = pair_edge_point->second;
		pair_edge_point++;
		Point second_point = pair_edge_point->second;

		if (position_point_relative_straight_line(first_point, second_point, currentPoint) < 0) {
			std::swap(first_point, second_point);
		}
		std::list<Half_Edge*> new_boundary;
		while (!checkInLine(edge->get_origin()->get_vertex_coordinates(), edge->get_twin()->get_origin()->get_vertex_coordinates(), first_point)) {
			edge = edge->get_next();
		}

		Vertex * new_vertex_first_point = voronoi_diagram->create_vertex(first_point);
		
		new_vertex_first_point->set_incident_half_edge(edge);
		edge->set_origin(new_vertex_first_point);
		
		while (!checkInLine(edge->get_origin()->get_vertex_coordinates(), edge->get_twin()->get_origin()->get_vertex_coordinates(), second_point)) {
			new_boundary.push_back(edge);
			edge = edge->get_next();
		}
		Vertex * new_vertex_second_point = voronoi_diagram->create_vertex(second_point);
		new_vertex_second_point->set_incident_half_edge(edge);
		

		Half_Edge * new_half_edge = voronoi_diagram->create_half_edge();
		Half_Edge * new_half_edge_twin = voronoi_diagram->create_half_edge();
		edge->get_twin()->set_origin(new_vertex_second_point);
		edge->get_twin()->set_prev(new_half_edge_twin);

		edge->set_next(new_half_edge);
		new_boundary.push_back(edge);

		new_half_edge->set_origin(new_vertex_second_point);
		new_half_edge->set_face(edge->get_face());
		new_half_edge->set_next(new_boundary.front());
		new_half_edge->set_prev(edge);
		new_half_edge->set_twin(new_half_edge_twin);

		new_half_edge_twin->set_origin(new_vertex_first_point);
		new_half_edge_twin->set_face(new_face_for_add_point);
		new_half_edge_twin->set_next(edge->get_twin());
		new_half_edge_twin->set_prev(new_boundary.front()->get_twin());
		new_half_edge_twin->set_twin(new_half_edge);

		new_boundary.push_back(new_half_edge);
		edge->get_face()->set_boundary(new_boundary);

		new_boundary = new_face_for_add_point->get_boundary();

		new_half_edge = voronoi_diagram->create_half_edge();
		new_half_edge_twin = voronoi_diagram->create_half_edge();
		new_half_edge->set_origin(new_vertex_first_point);
		new_half_edge->set_face(new_face_for_add_point);

		if (new_boundary.size() != 0) {
			new_half_edge->set_next(new_boundary.back());
			new_half_edge_twin->set_prev(new_boundary.back()->get_twin());

			new_half_edge->get_next()->set_prev(new_half_edge);
			new_half_edge_twin->get_prev()->set_next(new_half_edge_twin);
		}

		new_half_edge->set_twin(new_half_edge_twin);

		new_half_edge_twin->set_origin(new_vertex_second_point);
		new_half_edge_twin->set_face(edge->get_face());
		new_half_edge_twin->set_twin(new_half_edge);

		new_face_for_add_point->set_boundary(new_half_edge);

		++pair_edge_point;
	}

	finish_boundary(new_face_for_add_point, new_face_for_add_point->get_boundary());

}

