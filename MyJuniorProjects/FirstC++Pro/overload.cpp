#include "overload.h"

int Data::staticval = 0; // 静态成员变量初始化
int Data::numOfInstances = 0; // 静态成员变量初始化

Data::Data() {
	// 每次创建一个Data对象时，实例数量加1
	numOfInstances++;
	data = 0; // 初始化非静态成员变量
}

Data::~Data() {
	// 每次销毁一个Data对象时，实例数量减1
	numOfInstances--;
}

int Data::getStaticVal() {
	//data++; // 不能访问非静态成员变量
	return staticval;
}

Point Point::operator+(const Point& other) const {
	Point result;
	result.x = x + other.x;
	result.y = y + other.y;
	return result;
}