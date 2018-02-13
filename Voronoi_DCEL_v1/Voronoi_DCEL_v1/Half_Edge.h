#pragma once
#include <utility>

class Vertex;
class Face;


class Half_Edge {

public:
	Half_Edge() :
		twin(NULL),
		next(NULL),
		prev(NULL),
		origin(NULL),
		face(NULL)
	{}
	~Half_Edge() {};

	inline Half_Edge * get_twin() const {
		return this->twin;
	}

	inline void set_twin(Half_Edge * twin_half_edge) {
		this->twin = twin_half_edge;
	}

	inline Half_Edge * get_next() const {
		return this->next;
	}

	inline void set_next(Half_Edge * next_half_edge) {
		this->next = next_half_edge;
	}

	inline Half_Edge * get_prev() const {
		return this->prev;
	}

	inline void set_prev(Half_Edge * prev_half_edge) {
		this->prev = prev_half_edge;
	}

	inline Vertex * get_origin() const {
		return this->origin;
	}

	inline void set_origin(Vertex * origin_vertex) {
		this->origin = origin_vertex;
	}

	inline Face * get_face() const {
		return this->face;
	}

	inline void set_face(Face * new_face) {
		this->face = new_face;
	}

private: 
	Half_Edge * twin;
	Half_Edge * next;
	Half_Edge * prev;
	Vertex * origin;
	Face * face;
};