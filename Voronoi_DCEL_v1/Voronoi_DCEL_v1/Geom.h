#pragma once
#include "Point.h"
#include "Half_Edge.h"
#include "Mesh.h"
bool belong_mesh(Point input_point, Mesh voronoi_mesh);

Point intersection_lines(std::pair<Point, Point> line1, std::pair<Point, Point> line2);