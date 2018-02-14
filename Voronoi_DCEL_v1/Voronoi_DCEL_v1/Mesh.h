#pragma once
#include <list>
#include "Face.h"
#include "Half_Edge.h"
#include "Vertex.h"
#include <vector>

class Mesh {

public:
	Mesh();
	~Mesh();

	void clear();
	
	bool is_empty() const;

	void insert(Vertex * vertex);
	void insert(Face * face);
	void insert(Half_Edge * edge);

	void remove(Vertex * vertex);
	void remove(Face * face);
	void remove(Half_Edge * half_edge);

	inline std::vector<Vertex*> get_vertex_list() {
		return vertex_list;
	}

	inline std::vector<Face*> get_face_list() {
		return face_list;
	}

	inline std::vector<Half_Edge*> get_half_edge_list() {
		return half_edge_list;
	}


	inline Half_Edge* create_half_edge() {
		half_edge_list.push_back(new Half_Edge);
		return half_edge_list[half_edge_list.size() - 1];
	}

	inline Vertex* create_vertex(Point p) {
		vertex_list.push_back(new Vertex(p));
		return vertex_list[vertex_list.size() - 1];
	}

	inline Face* create_face() {
		face_list.push_back(new Face);
		return face_list[face_list.size() - 1];
	}

	inline Face* create_face(Point input_point) {
		face_list.push_back(new Face(input_point));
		return face_list[face_list.size() - 1];
	}

	inline unsigned int get_num_faces() const { 
		return face_list.size();
	}

	inline unsigned int get_num_vertices() const { 
		return vertex_list.size();
	}

	inline unsigned int get_num_half_edges() const { 
		return half_edge_list.size();
	}

	inline void set_input_point(Point point) {
		this->input_point = point;
	}
	inline Point get_input_point() const {
		return input_point;
	}


private:
	std::vector<Face *> face_list;
	std::vector<Vertex *> vertex_list;
	std::vector<Half_Edge *> half_edge_list;

	Point input_point;
};