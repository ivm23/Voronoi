#include "Mesh.h"

Mesh::Mesh() {
}

Mesh::~Mesh() {
	this->clear();
}

void Mesh::clear() {
	this->face_list.clear();
	this->vertex_list.clear();
	this->half_edge_list.clear();
}

bool Mesh::is_empty() const{
	return (vertex_list.empty() && face_list.empty() && half_edge_list.empty());
}

/*void Mesh::insert(Vertex * vertex) {
	if (vertex) {
		int index = vertex_list.size();
		vertex_list.resize(index + 1);
		vertex_list[index] = new Vertex;
		(*vertex_list[index]).set_incident_half_edge((*vertex).get_incident_half_edge());
		(*vertex_list[index]).set_vertex_coordinates((*vertex).get_vertex_coordinates());
	}
}

void Mesh::insert(Half_Edge * half_edge) {
	if (half_edge) {
		int index = half_edge_list.size();
		half_edge_list.resize(index + 1);
		half_edge_list[index] = new Half_Edge;
		(*half_edge_list[index]).set_face((*half_edge).get_face());
		(*half_edge_list[index]).set_next((*half_edge).get_next());
		(*half_edge_list[index]).set_origin((*half_edge).get_origin());
		(*half_edge_list[index]).set_prev((*half_edge).get_prev());
		(*half_edge_list[index]).set_twin((*half_edge).get_twin());
	}
}

void Mesh::insert(Face * face) {
	if (face) {
		int index = face_list.size();
		face_list.resize(index + 1);
		face_list[index] = new Face;

	//	for each (auto b in (*face).get_boundary())
		{
			(*face_list[index]).set_boundary((*face).get_boundary());
		}
	
	}
}
*/

void Mesh::remove(Vertex * vertex) {
	if (vertex) {
		Half_Edge * half_edge = vertex->get_incident_half_edge();
		remove(half_edge);
		std::vector<Vertex*>::iterator it = std::find(vertex_list.begin(), vertex_list.end(), vertex);
		vertex_list.erase(it);		
		delete vertex;
	}
}

void Mesh::remove(Face * face) {
	if (face) {
		std::vector<Face*>::iterator it = std::find(face_list.begin(), face_list.end(), face);
		face_list.erase(it);
		delete face;
	}
}

void Mesh::remove(Half_Edge * half_edge) {
	if (half_edge) {
		auto face = half_edge->get_face();
		auto edge = face->get_boundary();
		for (std::list<Half_Edge*>::iterator it = edge.begin(); it != edge.end();) {
			if ((*it) == half_edge) {
				it = edge.erase(it);
			}
			else {
				++it;
			}
		}
		half_edge->get_face()->set_boundary(edge);

		std::vector<Half_Edge*>::iterator it = std::find(half_edge_list.begin(), half_edge_list.end(), half_edge);
		half_edge_list.erase(it);
		delete half_edge;
	}
}