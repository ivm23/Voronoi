#pragma once
#include <utility>

class Half_Edge;

class Face {
	
public:

	inline std::list<Half_Edge *> get_boundary() const {
		return this->boundary;
	}

	inline void set_boundary(std::list<Half_Edge *> boundary_of_face) {
		for each (auto b in boundary_of_face)
		{
			this->boundary.push_back(b);
		}
		
	}
	
private:
	std::list<Half_Edge *> boundary;
};
