#pragma once
#include "Mesh.h"
#include "Const_Values.h"
#include <vector>

class Voronoi_Diagram {

public:
	Voronoi_Diagram ();

	void add_new_voronoi_cell(Point point_to_add);

	inline std::vector<Mesh*> get_voronoi_diagram() const {
		return voronoi_diagram;
	}

private:
	
	std::vector<Mesh*> voronoi_diagram;

};

