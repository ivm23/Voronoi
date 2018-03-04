#pragma once
#include "Mesh.h"
#include "Geom.h"
#include "Const_Values.h"
#include <vector>

class Voronoi_Diagram {

public:
	std::pair<Half_Edge*, Point> first_intersect;
	Voronoi_Diagram (Point first_input_point);	
	void add_new_voronoi_cell(Point point_to_add, bool f);
	void finish_boundary(Face * face, std::list<Half_Edge*> &boundary);
	std::list<std::pair<Half_Edge*, Point>> get_list_face(Face* begin, Point add_point);

	inline Mesh* get_voronoi_diagram() const {
		return voronoi_diagram;
	}

	Face* point_belong_face(Point point);

private:
	
	Mesh* voronoi_diagram;

};

