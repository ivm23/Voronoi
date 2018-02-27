#pragma once
#include <utility>
#include "Point.h"

class Half_Edge;

class Face {
	
public:
	Face() {};
	Face(Point inPoint) : input_point(inPoint) {}


	inline std::list<Half_Edge *> get_boundary() const {
		return this->boundary;
	}

	inline void set_boundary(std::list<Half_Edge *> boundary_of_face) {
		this->boundary.clear();
		for each (auto b in boundary_of_face)
		{
			this->boundary.push_back(b);
		}
	}

	inline void set_boundary(Half_Edge* boundary_half_edge) {
		this->boundary.push_back(boundary_half_edge);
	}

	inline Point get_input_point() const {
		return this->input_point;
	}

	inline void set_input_point(Point input_point) {
		this->input_point = input_point;
	}
	
private:
	std::list<Half_Edge *> boundary;
	Point input_point;
};
