#pragma once

struct Point {
	double x;
	double y;

	Point(double a, double b) : x(a), y(b) {}

	bool operator==(const Point& other) {
		return this->x == other.x && this->y == other.y;
	}
};

