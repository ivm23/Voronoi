#pragma once
//#include "Const_Values.h"
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
	
	bool operator>(Point &other) {
		return (this->x > other.x || (this->x == other.x && this->y > other.y));
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
	double err = 0.05;
	bool equals(Point other) {
		return (other.x - err <= this->x && this->x <= other.x + err && other.y - err <= this->y && this->y <= other.y + err);
	}

};