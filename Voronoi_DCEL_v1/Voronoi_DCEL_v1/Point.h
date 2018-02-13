#pragma once

struct Point {
	double x;
	double y;

	Point() {}
	Point(double a, double b) : x(a), y(b) {}

	bool operator==(const Point& other) {
		return this->x == other.x && this->y == other.y;
	}
	bool operator!= (Point &other) {
		return !(*this == other);
	}

	Point & operator=(Point other) {
		this->x = other.x;
		this->y = other.y;
		return *this;
	}
	
	Point operator+(Point & other) {
		return Point(this->x + other.x, this->y + other.y);
	}

	Point operator-(Point& other) {
		return Point(this->x - other.x, this->y - other.y);
	}

	friend Point operator* (double scalar_number, Point & point) {
		return Point(scalar_number * point.x, scalar_number * point.y);
	}
};