#pragma once
#include <utility>
#include "Point.h"

class Half_Edge;

class Vertex {
public:

	Vertex() :
		vertex_coordinates(),
		incident_half_edge(NULL)
	{};

	Vertex(Point vertex) :
		vertex_coordinates(vertex),
		incident_half_edge(NULL)
	{};

	~Vertex() {};

	inline Half_Edge * get_incident_half_edge() const {
		return this->incident_half_edge;
	}

	inline void set_incident_half_edge(Half_Edge * edge) {
		this->incident_half_edge = edge;
	}

	inline Point get_vertex_coordinates() const {
		return this->vertex_coordinates;
	}

	inline void set_vertex_coordinates(Point coordinates) {
		this->vertex_coordinates = coordinates;
	}

	bool operator==(const Vertex& other) {
		return this->vertex_coordinates == other.vertex_coordinates;
	}

	bool operator!= (Vertex &other) {
		return !(*this == other);
	}

private:
	Point vertex_coordinates;
	Half_Edge * incident_half_edge;
};