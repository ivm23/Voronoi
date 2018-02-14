#pragma once
#include "Mesh.h"
#include "Geom.h"
#include "Const_Values.h"
#include <vector>

class Voronoi_Diagram {

public:
	Voronoi_Diagram (Point first_input_point);

	void add_new_voronoi_cell(Point point_to_add);

	inline std::vector<Mesh*> get_voronoi_diagram() const {
		return voronoi_diagram;
	}

	Mesh* point_belong_mesh(Point point);

	Mesh* get_next_mesh_to_change(Straight_Line circle_intersection_line, Mesh* mesh);

private:
	
	std::vector<Mesh*> voronoi_diagram;

};

