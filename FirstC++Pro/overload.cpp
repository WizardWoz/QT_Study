#include "overload.h"
Point Point::operator+(const Point& other) const {
	Point result;
	result.x = x + other.x;
	result.y = y + other.y;
	return result;
}