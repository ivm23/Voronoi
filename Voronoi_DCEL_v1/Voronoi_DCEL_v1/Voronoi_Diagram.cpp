#include"Voronoi_Diagram.h"

Voronoi_Diagram::Voronoi_Diagram() {

	int index = voronoi_diagram.size();
	voronoi_diagram.resize(index + 1);
	voronoi_diagram[index] = new Mesh;
	auto myMesh = voronoi_diagram[index];

	Half_Edge* frame_left_half_edge = (*myMesh).create_half_edge();
	Half_Edge* frame_up_half_edge = (*myMesh).create_half_edge();
	Half_Edge* frame_right_half_edge = (*myMesh).create_half_edge();
	Half_Edge* frame_down_half_edge = (*myMesh).create_half_edge();

	Half_Edge* frame_left_half_edge_twin = (*myMesh).create_half_edge();
	Half_Edge* frame_up_half_edge_twin = (*myMesh).create_half_edge();
	Half_Edge* frame_right_half_edge_twin = (*myMesh).create_half_edge();
	Half_Edge* frame_down_half_edge_twin = (*myMesh).create_half_edge();

	Vertex* frame_left_down_point = (*myMesh).create_vertex(FRAME_LEFT_DOWN);
	Vertex* frame_left_up_point = (*myMesh).create_vertex(FRAME_LEFT_UP);
	Vertex* frame_right_down_point = (*myMesh).create_vertex(FRAME_RIGHT_DOWN);
	Vertex* frame_right_up_point = (*myMesh).create_vertex(FRAME_RIGHT_UP);

	Face* frame_left_face = (*myMesh).create_face();
	Face* frame_up_face = (*myMesh).create_face();
	Face* frame_right_face = (*myMesh).create_face();
	Face* frame_down_face = (*myMesh).create_face();

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

	std::list<Half_Edge*> boundary_left;
	std::list<Half_Edge*> boundary_up;
	std::list<Half_Edge*> boundary_right;
	std::list<Half_Edge*> boundary_down;

	boundary_left.push_back(frame_left_half_edge);
	boundary_left.push_back(frame_up_half_edge);
	boundary_left.push_back(frame_right_half_edge);
	boundary_left.push_back(frame_down_half_edge);

	boundary_up.push_back(frame_up_half_edge);
	boundary_up.push_back(frame_right_half_edge);
	boundary_up.push_back(frame_down_half_edge);
	boundary_up.push_back(frame_left_half_edge);

	boundary_right.push_back(frame_right_half_edge);
	boundary_right.push_back(frame_down_half_edge);
	boundary_right.push_back(frame_left_half_edge);
	boundary_right.push_back(frame_up_half_edge);

	boundary_down.push_back(frame_down_half_edge);
	boundary_down.push_back(frame_left_half_edge);
	boundary_down.push_back(frame_up_half_edge);
	boundary_down.push_back(frame_right_half_edge);

	(*frame_left_face).set_boundary(boundary_left);
	(*frame_up_face).set_boundary(boundary_up);
	(*frame_right_face).set_boundary(boundary_right);
	(*frame_down_face).set_boundary(boundary_down);

	(*frame_left_half_edge).set_face(frame_left_face);
	(*frame_up_half_edge).set_face(frame_up_face);
	(*frame_right_half_edge).set_face(frame_right_face);
	(*frame_down_half_edge).set_face(frame_down_face);

	(*frame_left_half_edge_twin).set_face(frame_left_face);
	(*frame_up_half_edge_twin).set_face(frame_up_face);
	(*frame_right_half_edge_twin).set_face(frame_right_face);
	(*frame_down_half_edge_twin).set_face(frame_down_face);

	(*frame_left_down_point).set_incident_half_edge(frame_left_half_edge);
	(*frame_left_up_point).set_incident_half_edge(frame_up_half_edge);
	(*frame_right_up_point).set_incident_half_edge(frame_right_half_edge);
	(*frame_right_down_point).set_incident_half_edge(frame_down_half_edge);
};

void Voronoi_Diagram::add_new_voronoi_cell(Point point_to_add) {

}

