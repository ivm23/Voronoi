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
		for each (auto b in boundary_of_face)
		{
			this->boundary.push_back(b);
		}
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
